#pragma once

#include "Diffusion.h"

class SabrDiffusion 
    : public Diffusion
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    SabrDiffusion(const double beta, const double rho, const double volatility);
    virtual ~SabrDiffusion();

    /**************************************************************************
     * inherited  operators.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const;

private:
    /**************************************************************************
     * private variables
     **************************************************************************/
    const double _beta;
    const double _rho;
    const double _volatility;
};
