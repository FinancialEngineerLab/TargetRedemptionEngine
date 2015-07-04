#include "StochasticDifferentialEquationWithDifferentialFactory.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
StochasticDifferentialEquationWithDifferentialFactory::
    StochasticDifferentialEquationWithDifferentialFactory() 
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
    const boost::shared_ptr<const DifferentialDrift> differentialDiffusion = 
        makeDifferentialDiffusion();

    return boost::make_shared<StochasticDifferentialEquation>(
        stochasticDifferentiaEquation, differentialDrfit, differentialDiffusion);
}

