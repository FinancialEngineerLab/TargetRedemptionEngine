#include "PayOff.h"

PayOff::PayOff(
    const boost::shared_ptr<const PayOffFunction>& payOffFunction)
    :
    _payOffFunction(payOffFunction)
{
    
}

PayOff::~PayOff() 
{
}

double PayOff::operator()(
    const boost::numeric::ublas::vector<double>& underlyings)
{
    return _payOffFunction->operator()(underlyings);
}

void PayOff::differentiate()(
    const boost::numeric::ublas::vector<double>& underlyings,
    const boost::numeric::ublas::vector<double>& results)
{
    _payOffFunction->operator()(underlyings, results);
}

