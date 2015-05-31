#include "CashFlowPut.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowPut::CashFlowPut(
        const double strike)
    :
    _strike(strike)
{
}

CashFlowPut::~CashFlowPut() 
{
}

double operator()(
    const boost::numeric::ublas::vector<double>& path) const
{
    const double cashFlow = _cashFlow->operator()(path);

    return std::max(0.0, _strike - cashFlow);
}

