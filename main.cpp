#include "StochasticDifferentialEquation.h"
#include "BlackScholesFactory.h"
#include "EulerMaruyama.h"
#include "MersenneTwister.h"
#include "PlainVanillaPayOff.h"
#include "MonteCarloPricer.h"
#include "MonteCarloLogPricer.h"
#include "SabrFactory.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/math/distributions/normal.hpp>


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
    const double d1 = (log(spot / strike) + 0.5 * volatility * maturity) 
        / (volatility * sqrt(maturity));
    const double d2 = (log(spot / strike) - 0.5 * volatility * maturity) 
        / (volatility * sqrt(maturity));

    std::cout << "d1:" << d1 << std::endl;
    std::cout << "d2:" << d2 << std::endl;
    boost::math::normal normal;
    const double probability1 = boost::math::cdf(normal, d1);
    const double probability2 = boost::math::cdf(normal, d2);

    const double callPrice = 
        discountFactor * (spot * probability1 - strike * probability2);

    return callPrice;
}

int main()
{
    /**************************************************************************
     * Parameter settings.
     **************************************************************************/
    const double strike = 90.0;
    const double maturity = 5.0;
    const double spot = 100.0;
    const double volatility = 0.2;
    const double interestRate = 0.06;
    const double dividend = 0.03;
    const std::size_t numberOfTimeSteps = 30;
    const std::size_t numberOfSimulations = 10000;
    boost::numeric::ublas::vector<double> spots(1);
    spots[0] = spot;

    const double alpha = 0.15;
    const double beta = 0.5;
    const double rho = 0.0;
    const double volatilityOfVolatility = 0.2;
    boost::numeric::ublas::vector<double> sabrSpots(2);
    sabrSpots[0] = spot;
    sabrSpots[1] = alpha;

    const double discountFactor = 1.0;

    //SDE creation using Factory Class
    const BlackScholesFactory blackScholesFactory(
        interestRate, dividend, volatility);
    boost::shared_ptr<StochasticDifferentialEquation> blackScholes = 
        blackScholesFactory.makeStochasticDifferentialEquation();
    const LogBlackScholesFactory logBlackScholesFactory(
        interestRate, dividend, volatility);
    boost::shared_ptr<StochasticDifferentialEquation> logBlackScholes = 
        logBlackScholesFactory.makeStochasticDifferentialEquation();
    const SabrFactory sabrFactory(beta, volatilityOfVolatility);
    boost::shared_ptr<StochasticDifferentialEquation> sabr = 
        sabrFactory.makeStochasticDifferentialEquation();

    //discretization scheme.
    boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

    //random generator.
    boost::shared_ptr<MersenneTwister> mersenneTwister(
        new MersenneTwister(numberOfTimeSteps, 0));
    boost::shared_ptr<MersenneTwister> mersenneTwister2(
        new MersenneTwister(numberOfTimeSteps * 2, 0));

    //payoff function.
    boost::shared_ptr<PayOff> callPayOff(new CallOptionPayOff(strike));

    //create a pricer.
    const MonteCarloPricer pricer(
        blackScholes, eulerMaruyama, mersenneTwister, callPayOff);
    const MonteCarloLogPricer logPricer(
        logBlackScholes, eulerMaruyama, mersenneTwister, callPayOff);
    const MonteCarloPricer sabrPricer(
        sabr, eulerMaruyama, mersenneTwister2, callPayOff);

    //double price = pricer.simulatePrice(spots, maturity, numberOfSimulations, numberOfTimeSteps);
    //std::cout << price << std::endl;
    //double price2 = logPricer.simulatePrice(spots, maturity, numberOfSimulations, numberOfTimeSteps);
    //std::cout << price2 << std::endl;
    double price3 = sabrPricer.simulatePrice(sabrSpots, maturity, numberOfSimulations, numberOfTimeSteps);
    std::cout << "price3" << price3 << std::endl;

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
    std::cout << "price:" << callPrice << std::endl;
    
    {
        int a = 0;
        std::cin >> a;
    }

    return 0;

}


