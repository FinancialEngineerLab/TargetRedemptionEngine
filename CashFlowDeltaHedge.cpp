#include "CashFlowDeltaHedge.h"

#include <boost/math/distributions/normal.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowDeltaHedge::CashFlowDeltaHedge(
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
CashFlowDeltaHedge::~CashFlowDeltaHedge() 
{
}

double CashFlowDeltaHedge::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    double deltaHedge = 0.0;

    for (std::size_t timeIndex = 1; timeIndex < getCashFlowDateIndex(); 
            ++timeIndex) {
        const double timeStepSize = 
            _observedTimes[timeIndex] - _observedTimes[timeIndex - 1];
        const double discountFactor = 
            exp((_interestRate - _dividend) * timeStepSize);
        const double delta =  calculateDelta(path(0, timeIndex - 1), timeIndex - 1);

        deltaHedge += delta 
            * (path(0, timeIndex) - path(0, timeIndex - 1) * discountFactor); 
    }

    return -deltaHedge;
}

/******************************************************************************
 * For simplicity, the function calculates only the Blacksholes call delta.
 * One solution to change the model or payoff is making Delta Class,
 * which has a pure virtual funciton to return the calculated delta.
 ******************************************************************************/
double CashFlowDeltaHedge::calculateDelta(
    const double spot,
    const std::size_t timeIndex) const
{
    boost::math::normal normal(0.0, 1.0);
    const double d1 = 
        (log(spot / _strike) + 0.5 * _volatility * _volatility * _maturity) 
        / (_volatility * sqrt(_maturity));
    const double probability1 = boost::math::cdf(normal, d1);
    const double discountFactor = _discountFactors[timeIndex];

    return discountFactor *  probability1;
}

