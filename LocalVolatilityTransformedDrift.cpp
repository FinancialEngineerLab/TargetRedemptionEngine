#include "LocalVolatilityDrift.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
LocalVolatilityDrift::LocalVolatilityDrift(
    const Function1DStepWise& drift,
    const Function2DLogInterpolate& interpolatedVolatility) 
    :
    _drift(drift),
    _interpolatedVolatility(interpolatedVolatility)
{
}

LocalVolatilityDrift::~LocalVolatilityDrift() 
{
}

void LocalVolatilityDrift::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drifts) const
{
    drifts[0] =  _drift(time) + 0.5 * _interpolatedVolatility(time, states[0]);
}


