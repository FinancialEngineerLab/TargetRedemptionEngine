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
#include "CashFlowSpot.h"
#include "CashFlowCall.h"
#include "CashFlowSwap.h"
#include "CashFlowSwaption.h"
#include "CashFlowDeltaHedge.h"
#include "CashFlowGammaHedge.h"
#include "Expectation.h"
#include "ExpectationControlVariate.h"


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

inline boost::numeric::ublas::matrix<double> makeSabrCorrelationMatrix(
    const double rho)
{
    boost::numeric::ublas::matrix<double> correlation(2, 2, 0.0);
    correlation(0, 0) = 1;
    correlation(1, 0) = rho;
    correlation(1, 1) = sqrt(1.0 - rho * rho);

    return correlation;
}

/******************************************************************************
 * functions for the Libor Market Model.
 ******************************************************************************/
inline boost::numeric::ublas::vector<double> makeLiborMarketModelSpots(
    const std::size_t dimension)
{
    boost::numeric::ublas::vector<double> spots(dimension, 0.0);
    for (std::size_t dimensionIndex = 1; dimensionIndex <= dimension; 
        ++dimensionIndex) {
        //spots[dimensionIndex - 1] = dimensionIndex / 100.0 * 0.5;
        spots[dimensionIndex - 1] = 0.051;
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

inline boost::numeric::ublas::vector<double> makeLiborMarketModelTenor(
    const std::size_t dimension)
{
    boost::numeric::ublas::vector<double> tenor(dimension + 1, 0.0);
    for (std::size_t tenorIndex = 0; tenorIndex < dimension; 
        ++tenorIndex) {
        //maturities[maturityIndex - 1] = 0.5 * maturityIndex;
        tenor[tenorIndex] = 10.0 + 0.5 * tenorIndex;
    }

    return tenor;
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
            new PathSimulator(blackScholes, eulerMaruyama, mersenneTwister));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectationBase> expectation(
            new Expectation(presentValueCalculator));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            presentValueCalculator,
            expectation);


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
        const boost::numeric::ublas::matrix<double> sabrCorrelation = makeSabrCorrelationMatrix(rho);

        const std::size_t numberOfTimeSteps = 64;
        const std::size_t numberOfSimulations = 100;

        //SABR Model Creation by Factory Pattern.
        const SabrFactory sabrFactory(beta, volatilityOfVolatility, sabrCorrelation);
        boost::shared_ptr<const StochasticDifferentialEquation> sabr = 
            sabrFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps * 2, 0));

        const boost::shared_ptr<const PathSimulatorBase>  sabrPathSimulator(
            new PathSimulator(sabr, eulerMaruyama, mersenneTwister));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectationBase> expectation(
            new Expectation(presentValueCalculator));

        //pricer
        const MonteCarloPricer pricer(sabrPathSimulator, presentValueCalculator,
            expectation);

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

void calculateEuropeanCapletLiborMarketModel()
{
    /**************************************************************************
     * Euroepan caplet simulation under LIBOR Market Model.
     **************************************************************************/
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
        const boost::numeric::ublas::vector<double> tenor =
            makeLiborMarketModelTenor(numberOfBonds);
        const boost::numeric::ublas::matrix<double> correlation = 
            makeLiborMarketModelCorrelationMatrix(numberOfBonds);
        
        const std::size_t numberOfTimeSteps = 64;
        const std::size_t numberOfSimulations = 100;

        //LIBOR Market Model creation by Factory pattern.
        const LiborMarketModelFactory liborFactory(
            volatilities, tenor, correlation);
        boost::shared_ptr<const StochasticDifferentialEquation> libor = 
            liborFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps * numberOfBonds, 0));

        //path simulator
        const boost::shared_ptr<const PathSimulatorBase> pathSimulator(
            new PathSimulator(libor, eulerMaruyama, mersenneTwister));

        //make Indice
        std::vector<double> observedTimes(numberOfTimeSteps + 1);
        for (std::size_t timeIndex = 0; timeIndex < observedTimes.size(); ++timeIndex) {
            observedTimes[timeIndex] = timeIndex * (1.0 / 4.0);
        }
        //! tenorIndex to timeIndex. assuming that tenor is 6-month.
        //std::vector<std::size_t> tenorToTime(numberOfBonds + 1);
        //for (std::size_t tenorIndex = 0; tenorIndex < tenorToTime.size(); ++tenorIndex) {
        //    tenorToTime[tenorIndex] = (tenorIndex + 1) * 4;
        //}
        //! tenorIndex To AssetIndex.
        //std::vector<std::size_t> tenorToAsset(numberOfBonds);
        //for (std::size_t tenorIndex = 0; tenorIndex < numberOfBonds; ++tenorIndex) {
        //    tenorToAsset[tenorIndex] = tenorIndex;
        //}

        //cash flow.
        std::vector<std::size_t> tenorToTime(2);
        std::vector<std::size_t> tenorToAsset(1);
        std::vector< boost::shared_ptr<const CashFlow> > 
            europeanCaplets(numberOfBonds);
        for (std::size_t bondIndex = 0; bondIndex < numberOfBonds; ++bondIndex) {
            tenorToAsset[0] = bondIndex;
            tenorToTime[0] = (bondIndex + 40) * 1;
            tenorToTime[1] = (bondIndex + 41) * 1;
            const boost::shared_ptr<const CashFlowSwap> swap(
                new CashFlowSwap(observedTimes, tenorToTime, tenorToAsset, strike));
            europeanCaplets[bondIndex] = boost::shared_ptr<const CashFlow>(
                new CashFlowSwaption(swap->getCashFlowDateIndex(), swap));
        }

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //pricer
        std::vector< boost::shared_ptr<const MonteCarloPricer> > 
            pricers(numberOfBonds);
        for (std::size_t bondIndex = 0; bondIndex < numberOfBonds; ++bondIndex) {
            //present value calculator
            const boost::shared_ptr<const PresentValueCalculator> 
                presentValueCalculator(new PresentValueCalculator(
                    europeanCaplets[bondIndex], discountFactors));

            //expectation
            const boost::shared_ptr<ExpectationBase> expectation(
                new Expectation(presentValueCalculator));

            //pricer
            pricers[bondIndex] = boost::shared_ptr<const MonteCarloPricer>(
                new MonteCarloPricer(pathSimulator, presentValueCalculator,
                    expectation));
        }


        /**********************************************************************
         * Calculate Price.
         **********************************************************************/
        for (std::size_t bondIndex = 0; bondIndex < numberOfBonds; ++bondIndex) {
            const double price = pricers[bondIndex]->simulatePrice(spots, 
                numberOfSimulations, observedTimes, discountFactors);
            std::cout << "LIBOR Price[" << bondIndex << "]:" 
                << price << std::endl;
        }

        
        /**********************************************************************
         * European caplet analytic price.
         **********************************************************************/
        for (std::size_t bondIndex = 0; bondIndex < numberOfBonds; ++bondIndex) {
            const boost::numeric::ublas::vector<double> rowVolatility =
                boost::numeric::ublas::row(volatilities, bondIndex);
            const double volatility = sqrt(
                boost::numeric::ublas::inner_prod(rowVolatility, rowVolatility));

            const std::size_t tenorIndex0 = (bondIndex + 40) * 1;
            const std::size_t tenorIndex1 = (bondIndex + 41) * 1;
            const double period = 
                observedTimes[tenorIndex1] - observedTimes[tenorIndex0];
            const double price = period * calculateBlackFormula(
                spots[bondIndex], strike, volatility, 
                observedTimes[tenorIndex0], discountFactors[tenorIndex0]);

            std::cout << "tenor[" 
                << bondIndex << "]:" << observedTimes[tenorIndex0] << std::endl;
            std::cout << "discountFactor[" 
                << bondIndex << "]:" << discountFactors[tenorIndex0] << std::endl;
            std::cout << "spot[" 
                << bondIndex << "]:" << spots[bondIndex] << std::endl;
            std::cout << "vol[" 
                << bondIndex << "]:" << volatility << std::endl;
            std::cout << "LIBOR analytic Price[" 
                << bondIndex << "]:" << price << std::endl;
        }
         


        std::cout << std::endl;
    }
}

int main()
{
    /**************************************************************************
     * Programs on Chapter 4 in Clewlow.
     **************************************************************************/
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model. FIgure4.2.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = log(100.0);
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const LogBlackScholesFactory logBlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> logBlackScholes = 
            logBlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> blackScholesPathSimulator(
            new PathSimulator(logBlackScholes, eulerMaruyama, mersenneTwister));
        const boost::shared_ptr<const PathSimulatorBase> 
            logBlackScholesPathSimulator(
                new PathSimulatorExp(blackScholesPathSimulator));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectationBase> expectation(
            new Expectation(presentValueCalculator));

        //create a pricer.
        const MonteCarloPricer pricer(logBlackScholesPathSimulator, 
            presentValueCalculator, expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.2:" << price << std::endl;
    }

    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with Antithetic Variance Reductin. FIgure4.5.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = log(100.0);
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const LogBlackScholesFactory logBlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> logBlackScholes = 
            logBlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> blackScholesPathSimulator(
            new PathSimulator(logBlackScholes, eulerMaruyama, antitheticMersenneTwister));
        const boost::shared_ptr<const PathSimulatorBase> logBlackScholesPathSimulator(
            new PathSimulatorExp(blackScholesPathSimulator));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectationBase> expectation(
            new Expectation(presentValueCalculator));

        //create a pricer.
        const MonteCarloPricer pricer(logBlackScholesPathSimulator, 
            presentValueCalculator, expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.5:" << price << std::endl;
    }
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with a Delta-based Control Variate. FIgure4.9.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const BlackScholesFactory BlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
            BlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //observed Times
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> 
            blackScholesPathSimulator(
                new PathSimulator(blackScholes, eulerMaruyama, mersenneTwister));

        //cash flow
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));
        const boost::shared_ptr<const CashFlow>
            deltaHedge(new CashFlowDeltaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes, 
                europeanCall->getCashFlowDateIndex()));

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //control variates
        std::vector< boost::shared_ptr<const PresentValueCalculator> >
            controlVariates(1);
        boost::shared_ptr<const PresentValueCalculator>
            deltaControlVariate(
                new PresentValueCalculator(deltaHedge, discountFactors));
        controlVariates[0] = deltaControlVariate;

        //expectation
        const boost::shared_ptr<ExpectationBase> expectation(
            new ExpectationControlVariate(presentValueCalculator, 
                controlVariates));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            presentValueCalculator,
            expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.9:" << price << std::endl;
    }
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with a Delta-based Control Variate and Antithetic. FIgure4.11.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const BlackScholesFactory BlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
            BlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //observed Times
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> 
            blackScholesPathSimulator(
                new PathSimulator(blackScholes, eulerMaruyama, 
                antitheticMersenneTwister));

        //cash flow
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));
        const boost::shared_ptr<const CashFlow>
            deltaHedge(new CashFlowDeltaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes,
                europeanCall->getCashFlowDateIndex()));

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //control variates
        std::vector< boost::shared_ptr<const PresentValueCalculator> >
            controlVariates(1);
        boost::shared_ptr<const PresentValueCalculator>
            deltaControlVariate(
                new PresentValueCalculator(deltaHedge, discountFactors));
        controlVariates[0] = deltaControlVariate;

        //expectation
        const boost::shared_ptr<ExpectationBase> expectation(
            new ExpectationControlVariate(presentValueCalculator, 
                controlVariates));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            presentValueCalculator,
            expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.11:" << price << std::endl;
    }
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with a Delta-based Control Variate,
         * Gamma-based Control Variate and Antithetic. FIgure4.13.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const BlackScholesFactory BlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
            BlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //observed Times
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> 
            blackScholesPathSimulator(
                new PathSimulator(blackScholes, eulerMaruyama, 
                antitheticMersenneTwister));

        //cash flow
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));
        const boost::shared_ptr<const CashFlow>
            deltaHedge(new CashFlowDeltaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes,
                europeanCall->getCashFlowDateIndex()));
        const boost::shared_ptr<const CashFlow>
            gammaHedge(new CashFlowGammaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes, 
                europeanCall->getCashFlowDateIndex()));

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //control variates
        std::vector< boost::shared_ptr<const PresentValueCalculator> >
            controlVariates(2);
        boost::shared_ptr<const PresentValueCalculator>
            deltaControlVariate(
                new PresentValueCalculator(deltaHedge, discountFactors));
        boost::shared_ptr<const PresentValueCalculator>
            gammaControlVariate(
                new PresentValueCalculator(gammaHedge, discountFactors));
        controlVariates[0] = deltaControlVariate;
        controlVariates[1] = gammaControlVariate;

        //expectation
        const boost::shared_ptr<ExpectationBase> expectation(
            new ExpectationControlVariate(presentValueCalculator, 
                controlVariates));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            presentValueCalculator,
            expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.13:" << price << std::endl;
    }

    {
        int a = 0;
        std::cin >> a;
    }

    return 0;

}


