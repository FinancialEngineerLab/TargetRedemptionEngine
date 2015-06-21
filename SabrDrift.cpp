#include "SabrDrift.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
SabrDrift::SabrDrift() 
{
}

SabrDrift::~SabrDrift() 
{
}

void SabrDrift::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drifts) const
{
    drifts[0] = 0.0;
    drifts[1] = 0.0;
}
