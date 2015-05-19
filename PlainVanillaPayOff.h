#pragma once

#include "PayOff.h"

class CallOptionPayOff 
    : public PayOff
{
public:
    CallOptionPayOff(const double strike);
    virtual ~CallOptionPayOff();

    virtual double payOffFunction(
        const boost::numeric::ublas::vector<double>& spots) const;
    
private:
    const double _strike;            
};

