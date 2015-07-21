#include "StochasticDifferentialEquation.h"
#include "BlackScholesFactory.h"
#include "SabrFactory.h"
#include "LiborMarketModelFactory.h"
#include "EulerMaruyama.h"
#include "MersenneTwister.h"
#include "AntitheticRandom.h"
#include "MonteCarloPricer.h"
#include "PathSimulator.h"
#include "PathSimulatorExp.h"
#include "CashFlowCall.h"
#include "CashFlowSwap.h"
#include "CashFlowSwaption.h"
#include "CashFlowCaplet.h"
#include "Expectator.h"
#include "ExpectatorControlVariate.h"
#include "Maturities.h"
#include "Tenor.h"
#include "LiborMarketModelWithDifferentialFactory.h"
#include "Expectators.h"
#include "DeltaOperatorGenerator.h"
#include "PathwiseDeltaCalculator.h"
#include "FunctionCaplet.h"
#include "MonteCarloPricerMultiDimensional.h"

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/math/distributions/normal.hpp>


/******************************************************************************
 * functions for the SABR model.
 ******************************************************************************/
inline double calculateSabrTemporaryVariable1(
    const double spot,
    const double strike,
    const double volatilityOfVolatility,
    const double alpha,
    const double beta)
{
    return (volatilityOfVolatility / alpha) 
        * pow((spot * strike), (1.0 - beta)/2.0) * log(spot / strike);
}

inline double calculateSabrTemporaryVariable2(
    const double rho,
    const double z)
{
    return log((sqrt(1.0 - 2.0 * rho * z + z * z) + z - rho) / (1.0 - rho));
}

inline double calculateSabrImpliedVolatility(
    const double spot,
    const double strike,
    const double alpha,
    const double beta,
    const double rho,
    const double maturity,
    const double volatilityOfVolatility)
{
    const double z = calculateSabrTemporaryVariable1(
        spot, strike, volatilityOfVolatility, alpha, beta);
    std::cout << "z:" << z << std::endl;
    const double x = calculateSabrTemporaryVariable2(rho, z);
    std::cout << "x:" << x << std::endl;

    const double multiplier = alpha 
        / (pow(spot * strike, (1.0 - beta)/2.0) 
        * (1.0 + (pow(1.0 - beta, 2.0) / 24.0) * pow(log(spot / strike), 2.0) 
            + (pow(1.0 - beta, 4.0) / 1920.0) * pow(spot / strike, 4.0) ));
    std::cout << "multiplier:" << multiplier << std::endl;
    const double series = 
        1.0 
        + (pow(1.0 - beta, 2.0) / 24.0 * pow(alpha, 2.0) 
            / pow(spot * strike, 1.0 - beta) 
        + 1.0 / 4.0 * rho * beta * volatilityOfVolatility * alpha 
            / pow(spot * strike, (1.0 - beta) / 2.0)
        + (2.0 - 3.0 * pow(rho, 2.0)) / 24.0 * pow(volatilityOfVolatility, 2.0))
            * maturity;
    std::cout << "series:" << series << std::endl;
    const double impliedVolatility = multiplier * (z / x) * series;

    return impliedVolatility;
}

inline double calculateSabrAtTheMoneyImpliedVolatility(
    const double spot,
    const double strike,
    const double alpha,
    const double beta,
    const double rho,
    const double maturity,
    const double volatilityOfVolatility)
{
    const double multiplier = alpha / pow(spot, (1.0 - beta));
    std::cout << "multiplier:" << multiplier << std::endl;
    const double series = 
        1.0 
        + (pow(1.0 - beta, 2.0) / 24.0 * pow(alpha, 2.0) 
            / pow(spot, 2.0 - 2.0 * beta) 
        + 1.0 / 4.0 * rho * beta * volatilityOfVolatility * alpha 
            / pow(spot, 1.0 - beta)
        + (2.0 - 3.0 * pow(rho, 2.0)) / 24.0 * pow(volatilityOfVolatility, 2.0))
            * maturity;
    std::cout << "series:" << series << std::endl;
    const double impliedVolatility = multiplier *  series;

    return impliedVolatility;
}


inline double calculateBlackFormula(
    const double spot,
    const double strike,
    const double volatility,
    const double maturity,
    const double discountFactor)
{
    const double d1 = 
        (log(spot / strike) + 0.5 * volatility * volatility * maturity) 
        / (volatility * sqrt(maturity));
    const double d2 = 
        (log(spot / strike) - 0.5 * volatility * volatility * maturity) 
        / (volatility * sqrt(maturity));

    std::cout << "d1:" << d1 << std::endl;
    std::cout << "d2:" << d2 << std::endl;
    boost::math::normal normal(0.0, 1.0);
    const double probability1 = boost::math::cdf(normal, d1);
    const double probability2 = boost::math::cdf(normal, d2);

    const double callPrice = 
        discountFactor * (spot * probability1 - strike * probability2);

    return callPrice;
}

inline boost::numeric::ublas::matrix<double> makeSabrDecomposedCorrelationMatrix(
    const double rho)
{
    boost::numeric::ublas::matrix<double> decomposedCorrelation(2, 2, 0.0);
    decomposedCorrelation(0, 0) = 1;
    decomposedCorrelation(1, 0) = rho;
    decomposedCorrelation(1, 1) = sqrt(1.0 - rho * rho);

    return decomposedCorrelation;
}

/******************************************************************************
 * functions for the Libor Market Model.
 ******************************************************************************/
inline boost::numeric::ublas::vector<double> makeLiborMarketModelSpots(
    const std::size_t dimension)
{
    boost::numeric::ublas::vector<double> spots(dimension, 0.0);
    for (std::size_t dimensionIndex = 0; dimensionIndex < dimension; 
        ++dimensionIndex) {
        //spots[dimensionIndex - 1] = dimensionIndex / 100.0 * 0.5;
        spots[dimensionIndex] = 0.051;
    }

    return spots;
}

inline boost::numeric::ublas::matrix<double> makeLiborMarketModelVolatilities(
    const std::size_t dimension)
{
    boost::numeric::ublas::matrix<double> 
        volatilities(dimension, dimension, 0.0);
    for (std::size_t rowIndex = 1; rowIndex <= dimension; ++rowIndex) {
        for (std::size_t columnIndex = 0; columnIndex < rowIndex; ++columnIndex) {
            //volatilities(rowIndex - 1, columnIndex) = 0.2;
        }
        volatilities(rowIndex - 1, rowIndex - 1) = 0.2;
    }

    return volatilities;
}

inline boost::numeric::ublas::matrix<double> 
    makeLiborMarketModelCorrelationMatrix(const std::size_t dimension)
{
    const boost::numeric::ublas::matrix<double> correlation = 
        boost::numeric::ublas::identity_matrix<double>(dimension);

    return correlation;
}

/******************************************************************************
 * some utility functions.
 ******************************************************************************/
inline std::vector<double> makeObservedTimes(
    const double maturity, const std::size_t numberOfTimeSteps)
{
    assert(maturity > 0.0);
    assert(numberOfTimeSteps > 0.0);

    const double timeStepSize = maturity / numberOfTimeSteps;
    std::vector<double> observedTimes(numberOfTimeSteps + 1 , 0.0);

    double time = 0.0;
    for (std::size_t timeIndex = 0; timeIndex < numberOfTimeSteps; 
        ++timeIndex) {
        observedTimes[timeIndex] = time;
        time += timeStepSize;
    }
    observedTimes[numberOfTimeSteps] = maturity;

    return observedTimes;
}

inline boost::numeric::ublas::vector<double> makeDiscountFactors(
    const double rate,
    const std::vector<double>& observedTimes)
{
    boost::numeric::ublas::vector<double> discountFactors(observedTimes.size(), 0.0);

    for (std::size_t timeIndex = 0; timeIndex < observedTimes.size(); ++timeIndex) {
        discountFactors[timeIndex] = exp(-rate * observedTimes[timeIndex]);
    }

    return discountFactors;
}

void calculateEuropeanCallBlackScholes()
{
    /**************************************************************************
     * European Call BlackScholes Model Simulation.
     **************************************************************************/
    {
        /**********************************************************************
         * Parameter settings.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        const double spot = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = spot;
        const std::size_t numberOfTimeSteps = 64;
        const std::size_t numberOfSimulations = 10000;

        //BlackScholes Model creation by Factory patter.
        const BlackScholesFactory blackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
            blackScholesFactory.makeStochasticDifferentialEquation();
        //Logarithmic BlackScholes Model by Factory patter.
        //const LogBlackScholesFactory logBlackScholesFactory(
        //    interestRate, dividend, volatility);
        //boost::shared_ptr<const StochasticDifferentialEquation> 
        //  logBlackScholes = 
        //      logBlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase>  blackScholesPathSimulator(
            new PathSimulator(blackScholes, eulerMaruyama));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlowCalculator> 
            cashFlowCall(new CashFlowCall(strike, 0, observedTimes.size() - 1));
        const boost::shared_ptr<const CashFlow> 
            europeanCall(new CashFlow(cashFlowCall, 0));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectatorBase> expectation(
            new Expectator(presentValueCalculator));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            expectation,
            mersenneTwister);


        /**********************************************************************
         * Calculate price.
         **********************************************************************/
        double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "BlackScholes price:" << price  << std::endl;
        //double price = logPricer.simulatePrice(
        //    spots, maturity, numberOfSimulations, numberOfTimeSteps);
        //std::cout << price << std::endl;
        
        std::cout << std::endl;
    }
}

void calculateEuropeanCallSABR()
{
    /**************************************************************************
     * European Call SABR Model Simulation.
     **************************************************************************/
    {
        /**********************************************************************
         * Parameter settings.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        const double spot = 100.0;
        const double interestRate = 0.06;

        const double alpha = 0.2;
        const double beta = 1.0;
        const double rho = 0.5;
        const double volatilityOfVolatility = 0.2;
        boost::numeric::ublas::vector<double> spots(2);
        spots[0] = 100.0;
        spots[1] = alpha;
        const boost::numeric::ublas::matrix<double> sabrCorrelation = 
            makeSabrDecomposedCorrelationMatrix(rho);

        const std::size_t numberOfTimeSteps = 64;
        const std::size_t numberOfSimulations = 100;

        //SABR Model Creation by Factory Pattern.
        const SabrFactory sabrFactory(
            beta, volatilityOfVolatility, sabrCorrelation);
        boost::shared_ptr<const StochasticDifferentialEquation> sabr = 
            sabrFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps * 2, 0));

        const boost::shared_ptr<const PathSimulatorBase>  sabrPathSimulator(
            new PathSimulator(sabr, eulerMaruyama));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlowCalculator> 
            cashFlowCall(new CashFlowCall(strike, 0, observedTimes.size() - 1));
        const boost::shared_ptr<const CashFlow> 
            europeanCall(new CashFlow(cashFlowCall, 0));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectatorBase> expectation(
            new Expectator(presentValueCalculator));

        //pricer
        const MonteCarloPricer pricer(sabrPathSimulator, 
            expectation, mersenneTwister);

        /**********************************************************************
         * Calculate Price.
         **********************************************************************/
        double price = pricer.simulatePrice(spots, 
            numberOfSimulations, observedTimes, discountFactors);
        std::cout << "SABR Price:" << price << std::endl;

        /**********************************************************************
         * SABR Model analytic price.
         **********************************************************************/
        double impliedVolatility;
        if (spot == strike) {
            impliedVolatility = calculateSabrAtTheMoneyImpliedVolatility(
                spot, strike, alpha, beta, rho, maturity, volatilityOfVolatility);
        } else {
            impliedVolatility = calculateSabrImpliedVolatility(
                spot, strike, alpha, beta, rho, maturity, volatilityOfVolatility);
        }
        std::cout << "impliedVolatility:" << impliedVolatility << std::endl;

        const double discountFactor = exp(-interestRate * maturity);
        const double callPrice = calculateBlackFormula(
            spot, strike, impliedVolatility, maturity, discountFactor);
        std::cout << "imp price:" << callPrice << std::endl;
        
        std::cout << std::endl;
    }

}

/*****""""*********************************************************************
 * Euroepan caplet simulation under LIBOR Market Model.
 **""""************************************************************************/
void calculateEuropeanCapletLiborMarketModel()
{
    /**********************************************************************
     * Parameter settings.
     **********************************************************************/
    const double strike = 0.05;
    const double interestRate = 0.006;
    const std::size_t numberOfBonds = 5;
    const boost::numeric::ublas::vector<double> spots =
        makeLiborMarketModelSpots(numberOfBonds);
    const boost::numeric::ublas::matrix<double> volatilities =
        makeLiborMarketModelVolatilities(numberOfBonds);
    const boost::numeric::ublas::matrix<double> correlation = 
        makeLiborMarketModelCorrelationMatrix(numberOfBonds);

    const std::size_t numberOfTimeSteps = 32;
    const std::size_t numberOfSimulations = 100;

    //make Indice
    std::vector<double> observedTimes(numberOfTimeSteps + 1);
    for (std::size_t timeIndex = 0; timeIndex < observedTimes.size(); 
        ++timeIndex) {
        observedTimes[timeIndex] = timeIndex * (1.0 / 4.0);
    }
    std::vector<std::size_t> maturitiesIndice(numberOfBonds);
    maturitiesIndice[0] = 4;
    maturitiesIndice[1] = 8;
    maturitiesIndice[2] = 12;
    maturitiesIndice[3] = 16;
    maturitiesIndice[4] = 20;
    //Maturities maturities(observedTimes, maturitiesIndex);
    boost::shared_ptr<Maturities> maturities(
        new Maturities(observedTimes, maturitiesIndice));

    std::vector<std::size_t> tenorToMaturityIndice(2);
    tenorToMaturityIndice[0] = 0;
    tenorToMaturityIndice[1] = 1;
    const boost::shared_ptr<const Tenor> tenor(
        new Tenor(maturities, tenorToMaturityIndice));

    //LIBOR Market Model creation by Factory pattern.
    const LiborMarketModelFactory liborFactory(
        volatilities, maturities, correlation);
    boost::shared_ptr<const StochasticDifferentialEquation> libor = 
        liborFactory.makeStochasticDifferentialEquation();

    //discretization scheme.
    boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

    //random number generator.
    boost::shared_ptr<MersenneTwister> mersenneTwister(
        new MersenneTwister(numberOfTimeSteps * numberOfBonds, 0));

    //path simulator
    const boost::shared_ptr<const PathSimulatorBase> pathSimulator(
        new PathSimulator(libor, eulerMaruyama));

    //cash flow.
    const boost::shared_ptr<const CashFlowCalculator> cashFlowCaplet(
        new CashFlowCaplet(strike, tenor));
    const boost::shared_ptr<const CashFlow> caplet(
        new CashFlow(cashFlowCaplet, tenor->translateTenorIndexToTimeIndex(1)));
    //discount factors
    const boost::numeric::ublas::vector<double> discountFactors =
        makeDiscountFactors(interestRate, observedTimes);

    //present value calculator
    const boost::shared_ptr<const PresentValueCalculator> 
        presentValueCalculator(
            new PresentValueCalculator(caplet, discountFactors));

    //expectation
    const boost::shared_ptr<ExpectatorBase> expectation(
        new Expectator(presentValueCalculator));

    //pricer
    boost::shared_ptr<const MonteCarloPricer> pricer(
        new MonteCarloPricer(pathSimulator, 
            expectation, mersenneTwister));

    /**********************************************************************
     * Calculate Price.
     **********************************************************************/
    {
        const double price = pricer->simulatePrice(spots, 
            numberOfSimulations, observedTimes, discountFactors);
        std::cout << "LIBOR Price:" << price << std::endl;
    }
    
    /**********************************************************************
     * European caplet analytic price.
     **********************************************************************/
    {
        std::cout << std::endl;
        const boost::numeric::ublas::vector<double> rowVolatility =
            boost::numeric::ublas::row(volatilities, tenor->translateTenorIndexToAssetIndex(0));
        const double volatility = sqrt(
            boost::numeric::ublas::inner_prod(rowVolatility, rowVolatility));

        const double period = tenor->operator[](1) - tenor->operator[](0);
        const double price = period * calculateBlackFormula(
            spots[tenor->translateTenorIndexToAssetIndex(0)], strike, volatility, 
            tenor->operator[](0), discountFactors[tenor->translateTenorIndexToTimeIndex(1)]);

        std::cout << "tenor:" << tenor->operator[](0) << std::endl;
        std::cout << "DF:" << discountFactors[tenor->translateTenorIndexToTimeIndex(1)] << std::endl;
        std::cout << "spot:" << spots << std::endl;
        std::cout << "vol:" << volatility << std::endl;
        std::cout << "LIBOR analytic Price:" << price << std::endl;
    }

    std::cout << std::endl;
}

void calculatePathwiseDelta()
{
    /**********************************************************************
     * Parameter settings.
     **********************************************************************/
    const double strike = 0.05;
    const double interestRate = 0.006;
    const std::size_t numberOfBonds = 5;
    const boost::numeric::ublas::vector<double> spot =
        makeLiborMarketModelSpots(numberOfBonds);
    const boost::numeric::ublas::matrix<double> volatilities =
        makeLiborMarketModelVolatilities(numberOfBonds);
    const boost::numeric::ublas::matrix<double> correlation = 
        makeLiborMarketModelCorrelationMatrix(numberOfBonds);

    const std::size_t numberOfTimeSteps = 32;
    const std::size_t numberOfSimulations = 100;

    //make Indice
    std::vector<double> observedTimes(numberOfTimeSteps + 1);
    for (std::size_t timeIndex = 0; timeIndex < observedTimes.size(); 
        ++timeIndex) {
        observedTimes[timeIndex] = timeIndex * (1.0 / 4.0);
    }
    std::vector<std::size_t> maturitiesIndice(numberOfBonds);
    maturitiesIndice[0] = 4;
    maturitiesIndice[1] = 8;
    maturitiesIndice[2] = 12;
    maturitiesIndice[3] = 16;
    maturitiesIndice[4] = 20;
    //Maturities maturities(observedTimes, maturitiesIndex);
    boost::shared_ptr<Maturities> maturities(
        new Maturities(observedTimes, maturitiesIndice));

    std::vector<std::size_t> tenorToMaturityIndice(2);
    tenorToMaturityIndice[0] = 0;
    tenorToMaturityIndice[1] = 1;
    const boost::shared_ptr<const Tenor> tenor(
        new Tenor(maturities, tenorToMaturityIndice));

    //LIBOR Market Model Factory.
    const boost::shared_ptr<const LiborMarketModelFactory> liborFactory(
        new LiborMarketModelFactory(volatilities, maturities, correlation));

    //Libor market model with differential of drift and diffusion.
    const boost::shared_ptr<const LiborMarketModelWithDifferentialFactory>
        liborDifferentialFactory(new
            LiborMarketModelWithDifferentialFactory(liborFactory, 
                volatilities, maturities, correlation));
    boost::shared_ptr<const StochasticDifferentialEquationWithDifferential>
        liborDifferential = 
            liborDifferentialFactory->
                makeStochasticDifferentialEquationWithDifferential();

    //discretization scheme.
    boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

    //random number generator.
    boost::shared_ptr<MersenneTwister> mersenneTwister(
        new MersenneTwister(numberOfTimeSteps * numberOfBonds, 0));

    //path simulator
    const boost::shared_ptr<const PathSimulatorBase> pathSimulator(
        new PathSimulator(liborDifferential, eulerMaruyama));

    //discount factors
    const boost::numeric::ublas::vector<double> discountFactors =
        makeDiscountFactors(interestRate, observedTimes);

    //payOff funciton
    const boost::shared_ptr<FunctionCaplet>
        payOffFunction(new FunctionCaplet(strike, tenor->translateTenorIndexToAssetIndex(0)));

    //operator generator
    const boost::shared_ptr<DeltaOperatorGenerator>
        operatorGenerator(new DeltaOperatorGenerator(liborDifferential));

    //pathwise delta calculator
    const boost::shared_ptr<const PathwiseDeltaCalculator> 
        pathwiseDeltaCalculator(
            new PathwiseDeltaCalculator(observedTimes.size(), spot.size(),
                operatorGenerator, payOffFunction));

    //expectation
    //const boost::shared_ptr<ExpectatorsNull> expectatorNull(
    //    new ExpectatorsNull());
    const boost::shared_ptr<Expectators> expectator(
        new Expectators(spot.size(), pathwiseDeltaCalculator));

    //pricer
    boost::shared_ptr<const MonteCarloPricerMultiDimensional> pricer(
        new MonteCarloPricerMultiDimensional(pathSimulator, 
            expectator, mersenneTwister));

    /**************************************************************************
     * Calculate Price.
     **************************************************************************/
    {
        const boost::numeric::ublas::vector<double> price = 
            pricer->simulatePrice(spot, 
                numberOfSimulations, observedTimes, discountFactors);
        std::cout << "LIBOR Price:" << price << std::endl;
    }


    /**********************************************************************
     * European caplet analytic price.
     **********************************************************************/
    {
        std::cout << std::endl;
        const boost::numeric::ublas::vector<double> rowVolatility =
            boost::numeric::ublas::row(volatilities, tenor->translateTenorIndexToAssetIndex(0));
        const double volatility = sqrt(
            boost::numeric::ublas::inner_prod(rowVolatility, rowVolatility));

        const double period = tenor->operator[](1) - tenor->operator[](0);
        const double price = period * calculateBlackFormula(
            spot[tenor->translateTenorIndexToAssetIndex(0)], strike, volatility, 
            tenor->operator[](0), discountFactors[tenor->translateTenorIndexToTimeIndex(1)]);

        std::cout << "tenor:" << tenor->operator[](0) << std::endl;
        std::cout << "DF:" << discountFactors[tenor->translateTenorIndexToTimeIndex(1)] << std::endl;
        std::cout << "spot:" << spot << std::endl;
        std::cout << "vol:" << volatility << std::endl;
        std::cout << "LIBOR analytic Price:" << price << std::endl;
    }

    std::cout << std::endl;

}


int main()
{

    //calculateEuropeanCapletLiborMarketModel();
    calculatePathwiseDelta();

    {
        int a = 0;
        std::cin >> a;
    }

    return 0;

}


