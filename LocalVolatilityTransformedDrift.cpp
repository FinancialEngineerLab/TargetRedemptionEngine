#include "LocalVolatilityTransformedDrift.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
LocalVolatilityTransformedDrift::LocalVolatilityTransformedDrift(
    const Function1DStepWise& drift,
    const Function2DLogInterpolate& interpolatedVolatility) 
    :
    _drift(drift),
    _interpolatedVolatility(interpolatedVolatility)
{
}

LocalVolatilityTransformedDrift::~LocalVolatilityTransformedDrift() 
{
}

void LocalVolatilityTransformedDrift::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drifts) const
{
//    drifts[0] =  _drift(time) + 0.5 * _interpolatedVolatility(time, states[0])
//        - 0.5 * states[0] * _interpolatedVolatility.differentialByState(time, states[0]);
    drifts[0] =  _drift(time) + 0.5 * _interpolatedVolatility(time, states[0])
        - 0.5 * states[0] * _interpolatedVolatility.differentialByState(time, states[0]);

}


