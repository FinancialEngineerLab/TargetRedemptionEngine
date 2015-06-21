#include "BlackScholesDrift.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
BlackScholesDrift::BlackScholesDrift(
    const double interestRate, 
    const double dividend) 
    :
    _interestRate(interestRate),
    _dividend(dividend)
{
}

BlackScholesDrift::~BlackScholesDrift() 
{
}

void BlackScholesDrift::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drift) const
{
    drift[0] = (_interestRate - _dividend) * states[0];
}


/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
LogBlackScholesDrift::LogBlackScholesDrift(
    const double interestRate,
    const double dividend,
    const double volatility) 
    :
    _interestRate(interestRate),
    _dividend(dividend),
    _volatility(volatility)
{
}

LogBlackScholesDrift::~LogBlackScholesDrift() 
{
}

void LogBlackScholesDrift::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drift) const
{
    drift[0] = (_interestRate - _dividend - 0.5 * _volatility * _volatility);
}

