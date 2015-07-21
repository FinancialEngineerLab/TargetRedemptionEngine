#include "StochasticDifferentialEquationWithDifferential.h"
#include "DifferentialDrift.h"
#include "DifferentialDiffusion.h"

#include "boost/numeric/ublas/matrix.hpp"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
StochasticDifferentialEquationWithDifferential::
    StochasticDifferentialEquationWithDifferential(
        const boost::shared_ptr<const StochasticDifferentialEquation>& 
            stochasticDifferentiaEquation,
        const boost::shared_ptr<const DifferentialDrift> differentialDrift,
        const boost::shared_ptr<const DifferentialDiffusion> 
            differentialDiffusion)
        :
        StochasticDifferentialEquation(*stochasticDifferentiaEquation),
        _differentialDrift(differentialDrift),
        _differentialDiffusion(differentialDiffusion)
{
}
StochasticDifferentialEquationWithDifferential::
    ~StochasticDifferentialEquationWithDifferential()
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
void StochasticDifferentialEquationWithDifferential::
    calculateDifferentialDrift(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& drift) const
{
    _differentialDrift->calculate(time, states, drift);
}

void StochasticDifferentialEquationWithDifferential::
    calculateDifferentialDiffusion(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::multi_array<double, 3>& diffusion) const
{
    _differentialDiffusion->calculate(time, states, diffusion);
}

