#pragma once

#include "StochasticDifferentialEquation.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class StochasticDifferentialEquationFactory {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    StochasticDifferentialEquationFactory();
    virtual ~StochasticDifferentialEquationFactory();

    /**************************************************************************
     * member functions
     **************************************************************************/
    boost::shared_ptr<const StochasticDifferentialEquation> 
        makeStochasticDifferentialEquation() const;

private:
    virtual boost::shared_ptr<Drift> makeDrift() const = 0;
    virtual boost::shared_ptr<Diffusion> makeDiffusion() const = 0;
    virtual std::size_t makeDimension() const = 0;
    virtual std::size_t makeDimensionOfBrownianMotion() const = 0;
    
};

