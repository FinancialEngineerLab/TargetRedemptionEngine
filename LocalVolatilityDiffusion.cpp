#include "LocalVolatilityDiffusion.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
LocalVolatilityDiffusion::LocalVolatilityDiffusion(
    const Function2DLogInterpolate& interpolatedVolatility)
    :
    _interpolatedVolatility(interpolatedVolatility)
{
}

LocalVolatilityDiffusion::~LocalVolatilityDiffusion() 
{
}

/******************************************************************************
 * operators.
 ******************************************************************************/
void LocalVolatilityDiffusion::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& diffusion) const
{
    diffusion(0, 0) = _interpolatedVolatility(time, states[0]);
}

