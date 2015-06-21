#include "SabrDiffusion.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
SabrDiffusion::SabrDiffusion(
    const double beta, const double volatility, 
    const boost::numeric::ublas::matrix<double>& correlation) 
    :
    _beta(beta),
    _volatility(volatility),
    _correlation(correlation)
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
    //operation of matrix product: diffusionMatrix * correlationMatrix
    diffusion(0, 0) = pow(states[0], _beta) * states[1] * _correlation(0, 0);
    diffusion(0, 1) = 0.0;
    diffusion(1, 0) = _volatility * states[1] * _correlation(1, 0);
    diffusion(1, 1) = _volatility * states[1] * _correlation(1, 1);

}

