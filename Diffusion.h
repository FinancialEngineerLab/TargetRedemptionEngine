#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class Diffusion {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    Diffusion();
    virtual ~Diffusion();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const = 0;
};

