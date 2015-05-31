#include "PayOffSwaption.h"

PayOffSwaption::PayOffSwaption(const double strike) 
    :
    _strike(strike)
{
    
}
PayOffSwaption::~PayOffSwaption() 
{
}

double PayOffSwaption::payOffFunction(
    const boost::numeric::ublas::vector<double>& spots) const
{
    
}
