#pragma once

#include <boost/numeric/ublas/vector.hpp>

class Drift {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    Drift();
    virtual ~Drift();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const = 0;

private:

};

