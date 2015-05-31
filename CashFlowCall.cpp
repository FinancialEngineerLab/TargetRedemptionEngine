#include "CashFlowCall.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowCall::CashFlowCall(
        const double strike)
    :
    _strike(strike)
{
}

CashFlowCall::~CashFlowCall() 
{
}

double CashFlowCall::operator()(
    const boost::numeric::ublas::vector<double>& path) const
{
    const double cashFlow = _cashFlow->operator()(path);

    return std::max(0.0, cashFlow - strike);
}

