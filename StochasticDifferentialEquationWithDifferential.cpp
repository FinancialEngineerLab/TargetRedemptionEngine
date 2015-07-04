#include "StochasticDifferentialEquationWithDifferential.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
StochasticDifferentialEquationWithDifferential::
    StochasticDifferentialEquationWithDifferential(
        const StochasticDifferentialEquation stochasticDifferentiaEquation,
        const boost::shared_ptr<const DriftDifferential> differentialDrift,
        const boost::shared_ptr<const DiffusionDifferential> 
            differentialDiffusion)
        :
        StochasticDifferentialEquation(stochasticDifferentiaEquation),
        _differentialDrift(difrrentialDrift),
        _differentialDiffusion(differentialDiffusion)
{
}

StochasticDifferentialEquationWithDifferential::
    ~StochasticDifferentialEquationWithDifferential()
{
}

void StochasticDifferentialEquationWithDifferential::
    calculateDifferentialDrift(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const
{
    _differentialDrift->calculate(time, states, drift);
}

void StochasticDifferentialEquationWithDifferential::
    calculateDifferentialDiffusion(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const
{
    _differentialDiffusion->calculate(time, states, diffusion);
}

