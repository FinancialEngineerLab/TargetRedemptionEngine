#include "LocalVolatilityTransformedDiffusion.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
LocalVolatilityTransformedDiffusion::LocalVolatilityTransformedDiffusion()
{
}

LocalVolatilityTransformedDiffusion::~LocalVolatilityTransformedDiffusion() 
{
}

/******************************************************************************
 * operators.
 ******************************************************************************/
void LocalVolatilityTransformedDiffusion::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& diffusion) const
{
    diffusion(0, 0) = 1.0;
}

