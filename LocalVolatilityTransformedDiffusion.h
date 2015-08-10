#pragma once

#include "Diffusion.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class LocalVolatilityTransformedDiffusion : public Diffusion {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    LocalVolatilityTransformedDiffusion();
    virtual ~LocalVolatilityTransformedDiffusion();

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
};

