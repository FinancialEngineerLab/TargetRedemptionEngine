#include "CashFlowGammaHedge.h"

#include <boost/math/distributions/normal.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowGammaHedge::CashFlowGammaHedge(
    const double strike, 
    const double maturity, 
    const double volatility, 
    const double interestRate, 
    const double dividend,
    const boost::numeric::ublas::vector<double>& discountFactors,
    const std::vector<double>& observedTimes,
    const std::size_t cashFlowDateIndex) 
    :
    CashFlow(cashFlowDateIndex),
    _strike(strike),
    _maturity(maturity),
    _volatility(volatility),
    _interestRate(interestRate),
    _dividend(dividend),
    _discountFactors(discountFactors),
    _observedTimes(observedTimes)
{
}
CashFlowGammaHedge::~CashFlowGammaHedge() 
{
}

double CashFlowGammaHedge::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    double gammaHedge = 0.0;

    for (std::size_t timeIndex = 1; timeIndex < getCashFlowDateIndex(); 
            ++timeIndex) {
        const double timeStepSize = 
            _observedTimes[timeIndex] - _observedTimes[timeIndex - 1];
        const double deltaMultiplier = 
            exp((_interestRate - _dividend) * timeStepSize); 
        const double gammaMultiplier = 
            exp((2.0 * (_interestRate - _dividend) + _volatility * _volatility) 
                * timeStepSize) - 2.0 * deltaMultiplier + 1.0;
        const double gamma =  calculateGamma(path(0, timeIndex - 1), timeIndex - 1);

        gammaHedge += gamma 
            * ((path(0, timeIndex) - path(0, timeIndex - 1)) 
            * (path(0, timeIndex) - path(0, timeIndex - 1))
            -  path(0, timeIndex - 1) * path(0, timeIndex - 1) * gammaMultiplier); 
    }
    std::cout << "gmammm:" << gammaHedge << std::endl;

    return -0.5 * gammaHedge;
}

/******************************************************************************
 * For simplicity, the function calculates only the Blacksholes call gamma.
 * One solution to change the model or payoff is making Gamma Class,
 * which has a pure virtual funciton to return the calculated gamma.
 ******************************************************************************/
double CashFlowGammaHedge::calculateGamma(
    const double spot,
    const std::size_t timeIndex) const
{
    const double time = _observedTimes[timeIndex];
    if (time == 0.0) {
        return 0.0;
    }

    boost::math::normal normal(0.0, 1.0);
    const double d1 = 
        (log(spot / _strike) + 0.5 * _volatility * _volatility * _maturity) 
        / (_volatility * sqrt(_maturity));
    const double probability1 = boost::math::pdf(normal, d1);
    const double discountFactor = _discountFactors[timeIndex];
    const double divisor = spot * _volatility * sqrt(time);

   return discountFactor * probability1 / divisor;
}

