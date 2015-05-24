#include "StochasticDifferentialEquation.h"
#include "BlackScholesFactory.h"
#include "SabrFactory.h"
#include "LiborMarketModelFactory.h"
#include "EulerMaruyama.h"
#include "MersenneTwister.h"
#include "PlainVanillaPayOff.h"
#include "MonteCarloPricer.h"
#include "PathSimulator.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
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
    const double d1 = (log(spot / strike) + 0.5 * volatility * volatility * maturity) 
        / (volatility * sqrt(maturity));
    const double d2 = (log(spot / strike) - 0.5 * volatility * volatility * maturity) 
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
    for (std::size_t dimensionIndex = 0; dimensionIndex < dimension; ++dimensionIndex) {
        spots[dimensionIndex] = 1.0 - dimensionIndex / 100.0 * 0.5;
    }

    return spots;
}

inline boost::numeric::ublas::matrix<double> makeLiborMarketModelVolatilities(
    const std::size_t dimension)
{
    boost::numeric::ublas::matrix<double> volatilities(dimension, dimension, 0.0);
    for (std::size_t rowIndex = 0; rowIndex < dimension; ++rowIndex) {
        for (std::size_t columnIndex = 0; columnIndex < rowIndex; ++columnIndex) {
            volatilities(rowIndex, columnIndex) = 1.0;
        }
    }

    return volatilities;
}

inline boost::numeric::ublas::vector<double> makeLiborMarketModelMaturities(
    const std::size_t dimension)
{
    boost::numeric::ublas::vector<double> maturities(dimension, 0.0);
    for (std::size_t maturityIndex = 0; maturityIndex < dimension; ++maturityIndex) {
        maturities[maturityIndex] = 0.5 * maturityIndex;
    }
    return maturities;
}

inline boost::numeric::ublas::matrix<double> makeLiborMarketModelCorrelationMatrix(
    const std::size_t dimension)
{
    const boost::numeric::ublas::matrix<double> correlation = 
        boost::numeric::ublas::identity_matrix<double>(dimension);

    return correlation;
}

int main()
{
    /**************************************************************************
     * Parameter settings.
     **************************************************************************/
    //black shocles parameter settings
    const double strike = 100.0;
    const double maturity = 1.0;
    const double spot = 100.0;
    const double volatility = 0.2;
    const double interestRate = 0.06;
    const double dividend = 0.03;
    const std::size_t numberOfTimeSteps = 30;
    const std::size_t numberOfSimulations = 1000;
    boost::numeric::ublas::vector<double> spots(1);
    spots[0] = spot;

    //SABR parameter settings
    const double alpha = 0.2;
    const double beta = 1.0;
    const double rho = 0.5;
    const double volatilityOfVolatility = 0.2;
    boost::numeric::ublas::vector<double> sabrSpots(2);
    sabrSpots[0] = spot;
    sabrSpots[1] = alpha;
    const boost::numeric::ublas::matrix<double> sabrCorrelation = makeSabrCorrelationMatrix(rho);

    //LIBOR Market Model parameter settings
    const std::size_t numberOfBonds = 5;
    const boost::numeric::ublas::vector<double> liborSpots =
        makeLiborMarketModelSpots(numberOfBonds);
    const boost::numeric::ublas::matrix<double> liborVolatilities =
        makeLiborMarketModelVolatilities(numberOfBonds);
    const boost::numeric::ublas::vector<double> liborMaturities =
        makeLiborMarketModelMaturities(numberOfBonds + 1);
    const boost::numeric::ublas::matrix<double> liborCorrelation = 
        makeLiborMarketModelCorrelationMatrix(numberOfBonds);

    const double discountFactor = exp(-interestRate * maturity);

    //SDE creation by Factory Class
    const BlackScholesFactory blackScholesFactory(
        interestRate, dividend, volatility);
    boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
        blackScholesFactory.makeStochasticDifferentialEquation();
    const LogBlackScholesFactory logBlackScholesFactory(
        interestRate, dividend, volatility);
    boost::shared_ptr<const StochasticDifferentialEquation> logBlackScholes = 
        logBlackScholesFactory.makeStochasticDifferentialEquation();
    const SabrFactory sabrFactory(beta, volatilityOfVolatility, sabrCorrelation);
    boost::shared_ptr<const StochasticDifferentialEquation> sabr = 
        sabrFactory.makeStochasticDifferentialEquation();
    const LiborMarketModelFactory liborFactory(
        liborVolatilities, liborMaturities, liborCorrelation);
    boost::shared_ptr<const StochasticDifferentialEquation> libor = 
        liborFactory.makeStochasticDifferentialEquation();

    //discretization scheme.
    boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

    //random generator.
    boost::shared_ptr<MersenneTwister> mersenneTwister(
        new MersenneTwister(numberOfTimeSteps, 0));
    boost::shared_ptr<MersenneTwister> mersenneTwister2(
        new MersenneTwister(numberOfTimeSteps * 2, 0));
    boost::shared_ptr<MersenneTwister> liborMersenneTwister(
        new MersenneTwister(numberOfTimeSteps * numberOfBonds, 0));

    //payoff function.
    const boost::shared_ptr<const PayOff> callPayOff(new CallOptionPayOff(strike));

    //path simulator.
    const boost::shared_ptr<const PathSimulatorBase>  blackScholesPathSimulator(
        new PathSimulator(blackScholes, eulerMaruyama, mersenneTwister));
    const boost::shared_ptr<const PathSimulatorBase>  sabrPathSimulator(
        new PathSimulator(sabr, eulerMaruyama, mersenneTwister2));
    const boost::shared_ptr<const PathSimulatorBase>  liborPathSimulator(
        new PathSimulator(libor, eulerMaruyama, liborMersenneTwister));
    
    //create a pricer.
    const MonteCarloPricer pricer(blackScholesPathSimulator, callPayOff);
    const MonteCarloPricer sabrPricer(sabrPathSimulator, callPayOff);
    const MonteCarloPricer liborPricer(liborPathSimulator, callPayOff);

    //double price = pricer.simulatePrice(spots, maturity, numberOfSimulations, numberOfTimeSteps);
    //std::cout << "price:" << price << std::endl;
    //double price2 = logPricer.simulatePrice(spots, maturity, numberOfSimulations, numberOfTimeSteps);
    //std::cout << price2 << std::endl;
    double sabrPrice = sabrPricer.simulatePrice(sabrSpots, maturity, numberOfSimulations, numberOfTimeSteps);
    std::cout << "SABR Price:" << sabrPrice << std::endl;
    double liborPrice = liborPricer.simulatePrice(liborSpots, 
        liborMaturities[numberOfBonds], numberOfSimulations, numberOfTimeSteps);
    std::cout << "LIBOR Price:" << liborPrice << std::endl;

    double impliedVolatility;
    if (spot == strike) {
        impliedVolatility = calculateSabrAtTheMoneyImpliedVolatility(
            spot, strike, alpha, beta, rho, maturity, volatilityOfVolatility);
    } else {
        impliedVolatility = calculateSabrImpliedVolatility(
            spot, strike, alpha, beta, rho, maturity, volatilityOfVolatility);
    }

    std::cout << "impliedVolatility:" << impliedVolatility << std::endl;
    const double callPrice = calculateBlackFormula(
        spot, strike, impliedVolatility, maturity, discountFactor);
    std::cout << "imp price:" << callPrice << std::endl;
    
    {
        int a = 0;
        std::cin >> a;
    }

    return 0;

}


