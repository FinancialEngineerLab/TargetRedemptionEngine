#include "FunctionCall.h"


/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
FunctionCall::FunctionCall(const double strike) 
    :
    _strike(strike)
{
}

FunctionCall::~FunctionCall() 
{
}

double FunctionCall::operator()(
    const boost::numeric::ublas::vector<double>& spot)
{
    assert(spot.size() == 1);
    return spot[0] > _strike ? spot[0] - _strike : 0.0;
}

void FunctionCall::calculateDifferential(
    const boost::numeric::ublas::vector<double>& spot,
    boost::numeric::ublas::vector<double>& result)
{
    result[0] = spot[0] > _strike ? 1.0 : 0.0;
}

