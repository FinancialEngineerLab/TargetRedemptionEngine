#include "PlainVanillaPayOff.h"

CallOptionPayOff::CallOptionPayOff(const double strike) 
    :
    _strike(strike)
{
    
}
CallOptionPayOff::~CallOptionPayOff() 
{
}

double CallOptionPayOff::payOffFunction(
    const boost::numeric::ublas::vector<double>& spots) const
{
    return std::max(0.0, spots[0] - _strike);
}
