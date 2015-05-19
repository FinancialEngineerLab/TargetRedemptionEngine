#pragma once

#include "Drift.h"

class SabrDrift 
    : public Drift
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    SabrDrift();
    virtual ~SabrDrift();

    /**************************************************************************
     * inherited  operators.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const;

private:

};
