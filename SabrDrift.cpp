#include "SabrDrift.h"

SabrDrift::SabrDrift() 
{
}

SabrDrift::~SabrDrift() 
{
}

void SabrDrift::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drift) const
{
    drift[0] = 0.0;
    drift[1] = 0.0;
}
