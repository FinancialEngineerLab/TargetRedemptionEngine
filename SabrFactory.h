#pragma once

#include <boost/shared_ptr.hpp>

#include "StochasticDifferentialEquationFactory.h"


class SabrFactory :
    public StochasticDifferentialEquationFactory
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    SabrFactory(const double beta, const double volatility);
    virtual ~SabrFactory();

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
    const double _beta;
    const double _volatility;
    const std::size_t _dimension;
    const std::size_t _dimensionOfBrownianMotion;
};

