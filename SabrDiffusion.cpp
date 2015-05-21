#include "SabrDiffusion.h"

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
SabrDiffusion::SabrDiffusion(
    const double beta, const double volatility) 
    :
    _beta(beta),
    _volatility(volatility)

{
}

SabrDiffusion::~SabrDiffusion() 
{
}

/******************************************************************************
 * operators.
 ******************************************************************************/
void SabrDiffusion::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& diffusion) const
{
    diffusion(0, 0) = pow(states[0], _beta) * states[1];
    diffusion(0, 1) = 0.0;
    diffusion(1, 0) = 0.0;
    diffusion(1, 1) = _volatility * states[1];
}
