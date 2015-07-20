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
    return spot[0] > strike ? spot[0] - K : 0.0;
}

void FunctionCall::calculateDifferential(
    const boost::numeric::ublas::vector<double>& spot,
    boost::numeric::ublas::vector<double>& result)
{
    return spot[0] > strike ? 1.0 : 0.0;
}

