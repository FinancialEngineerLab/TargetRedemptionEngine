#pragma once

#include "StochasticDifferentialEquationFactory.h"
#include "StochasticDifferentialEquationWithDifferential.h"
#include "DifferentialDrift.h"
#include "DifferentialDiffusion.h"

#include <boost/shared_ptr.hpp>

class StochasticDifferentialEquationWithDifferentialFactory :
    public StochasticDifferentialEquationFactory
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
    virtual boost::shared_ptr<DifferentialDrift> 
        makeDifferentialDrift() const = 0;
    virtual boost::shared_ptr<DifferentialDiffusion> 
        makeDifferentialDiffusion() const = 0;
        
};

