#pragma once

#include <boost/shared_ptr.hpp>

#include "Function1DStepWise.h"
#include "Function2DLogInterpolate.h"
#include "StochasticDifferentialEquationFactory.h"


class LocalVolatilityFactory :
    public StochasticDifferentialEquationFactory {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    LocalVolatilityFactory(
        const Function1DStepWise& drift,
        const Function2DLogInterpolate& diffusion,
        const bool isTransformed);
    virtual ~LocalVolatilityFactory();

private:
    /**************************************************************************
     * inherited pure virtual funcitons.
     **************************************************************************/
    virtual boost::shared_ptr<Drift> makeDrift() const;
    virtual boost::shared_ptr<Diffusion> makeDiffusion() const;
    virtual std::size_t makeDimension() const;
    virtual std::size_t makeDimensionOfBrownianMotion() const;

    /**************************************************************************
     * private variables.
     **************************************************************************/
    const Function1DStepWise _drift;
    const Function2DLogInterpolate _diffusion;
    const std::size_t _dimension;
    const std::size_t _dimensionOfBrownianMotion;
    const bool _isTransformed;
};

