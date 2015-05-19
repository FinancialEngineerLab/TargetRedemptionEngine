#include "BlackScholesDiffusion.h"

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
BlackScholesDiffusion::BlackScholesDiffusion(const double volatility) 
    :
    _volatility(volatility)
{
}

BlackScholesDiffusion::~BlackScholesDiffusion() 
{
}

/******************************************************************************
 * operators.
 ******************************************************************************/
void BlackScholesDiffusion::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& diffusion) const
{
    diffusion(0, 0) = _volatility * states[0];
}


/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
LogBlackScholesDiffusion::LogBlackScholesDiffusion(const double volatility) 
    :
    _volatility(volatility)
{
}

LogBlackScholesDiffusion::~LogBlackScholesDiffusion() 
{
}

/******************************************************************************
 * operators.
 ******************************************************************************/
void LogBlackScholesDiffusion::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& diffusion) const
{
    diffusion(0, 0) = _volatility;
}

