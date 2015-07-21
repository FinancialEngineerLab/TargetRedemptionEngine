#pragma once

#include "StochasticDifferentialEquationFactory.h"
#include "StochasticDifferentialEquationWithDifferential.h"
#include "DifferentialDrift.h"
#include "DifferentialDiffusion.h"

#include <boost/shared_ptr.hpp>

class StochasticDifferentialEquationWithDifferentialFactory
{
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    StochasticDifferentialEquationWithDifferentialFactory(
        const boost::shared_ptr<const StochasticDifferentialEquationFactory>&
            factory);
    virtual ~StochasticDifferentialEquationWithDifferentialFactory();

    /**************************************************************************
     * member functions
     **************************************************************************/
    virtual boost::shared_ptr<
        const StochasticDifferentialEquationWithDifferential> 
            makeStochasticDifferentialEquationWithDifferential() const;
    
private:
    const boost::shared_ptr<const StochasticDifferentialEquationFactory>
        _factory;

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual boost::shared_ptr<const DifferentialDrift> 
        makeDifferentialDrift() const = 0;
    virtual boost::shared_ptr<const DifferentialDiffusion> 
        makeDifferentialDiffusion() const = 0;
        
};

