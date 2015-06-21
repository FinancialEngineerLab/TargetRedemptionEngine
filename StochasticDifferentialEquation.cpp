#include "StochasticDifferentialEquation.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
StochasticDifferentialEquation::StochasticDifferentialEquation(
    const boost::shared_ptr<Drift>& drift, 
    const boost::shared_ptr<Diffusion>& diffusion,
    const std::size_t dimension,
    const std::size_t dimensionOfBrownianMotion)
    :
    _drift(drift),
    _diffusion(diffusion),
    _dimension(dimension),
    _dimensionOfBrownianMotion(dimensionOfBrownianMotion)
{
}

StochasticDifferentialEquation::~StochasticDifferentialEquation() {
}

/******************************************************************************
 * member functions
 ******************************************************************************/
void StochasticDifferentialEquation::calculateDrift(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drift) const
{
    return (*_drift)(time, states, drift);
}

void StochasticDifferentialEquation::calculateDiffusion(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& diffusion) const
{
    return (*_diffusion)(time, states, diffusion);
}

