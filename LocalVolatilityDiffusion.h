#pragma once

#include "Diffusion.h"
#include "Function2DLogInterpolate.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class LocalVolatilityDiffusion : public Diffusion {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    LocalVolatilityDiffusion(
        const Function2DLogInterpolate& interpolatedVolatility);
    virtual ~LocalVolatilityDiffusion();

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
    const Function2DLogInterpolate& _interpolatedVolatility;
};

