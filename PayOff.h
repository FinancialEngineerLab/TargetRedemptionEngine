#pragma once

#include <boost/numeric/ublas/vector.hpp>

class PayOff {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    PayOff();
    virtual ~PayOff();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double payOffFunction(
        const boost::numeric::ublas::vector<double>& spots) const = 0;

private:
            
};

