#include "LocalVolatilityFactory.h"
#include "LocalVolatilityDrift.h"
#include "LocalVolatilityDiffusion.h"

#include <boost/make_shared.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
LocalVolatilityFactory::LocalVolatilityFactory(
    const Function1DStepWise& drift,
    const Function2DLogInterpolate& diffusion)
    :
    _drift(drift),
    _diffusion(diffusion),
    _dimension(1),
    _dimensionOfBrownianMotion(1)
{
}

LocalVolatilityFactory::~LocalVolatilityFactory()
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
boost::shared_ptr<Drift> LocalVolatilityFactory::makeDrift() const
{
    return boost::shared_ptr<LocalVolatilityDrift>(
        new LocalVolatilityDrift(_drift, _diffusion));
}

boost::shared_ptr<Diffusion> LocalVolatilityFactory::makeDiffusion() const
{
    return boost::shared_ptr<LocalVolatilityDiffusion>(
        new LocalVolatilityDiffusion(_diffusion));
}

std::size_t LocalVolatilityFactory::makeDimension() const
{
    return _dimension;
}
std::size_t LocalVolatilityFactory::makeDimensionOfBrownianMotion() const
{
    return _dimensionOfBrownianMotion;
}

