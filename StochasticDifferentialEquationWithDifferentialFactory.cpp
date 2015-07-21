#include "StochasticDifferentialEquationWithDifferentialFactory.h"

#include <boost/make_shared.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
StochasticDifferentialEquationWithDifferentialFactory::
    StochasticDifferentialEquationWithDifferentialFactory(
        const boost::shared_ptr<const StochasticDifferentialEquationFactory>&
            factory) 
    :
    _factory(factory)
{
}

StochasticDifferentialEquationWithDifferentialFactory::
    ~StochasticDifferentialEquationWithDifferentialFactory() 
{
}

    
boost::shared_ptr<const StochasticDifferentialEquationWithDifferential>
    StochasticDifferentialEquationWithDifferentialFactory::
        makeStochasticDifferentialEquationWithDifferential() const
{
    const boost::shared_ptr<const StochasticDifferentialEquation>
        stochasticDifferentiaEquation = 
            _factory->makeStochasticDifferentialEquation();
    const boost::shared_ptr<const DifferentialDrift> differentialDrift = 
        makeDifferentialDrift();
    const boost::shared_ptr<const DifferentialDiffusion> differentialDiffusion = 
        makeDifferentialDiffusion();

    return boost::make_shared<const StochasticDifferentialEquationWithDifferential>(
        stochasticDifferentiaEquation, differentialDrift, differentialDiffusion);
}


