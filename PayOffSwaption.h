#pragma once

#include "PayOff.h"

class PayOffSwaption 
    : public PayOff
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    PayOffSwaption(const double strike);
    virtual ~PayOffSwaption();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double payOffFunction(
        const boost::numeric::ublas::vector<double>& spots) const;

private:
    const double _strike;
            
};

