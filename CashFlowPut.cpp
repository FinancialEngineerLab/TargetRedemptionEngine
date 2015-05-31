#include "CashFlowPut.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowPut::CashFlowPut(
    const std::size_t timeIndex, const double strike,
    const boost::shared_ptr<const CashFlow> cashFlow)
    :
    CashFlow(timeIndex),
    _strike(strike),
    _cashFlow(cashFlow)
{
}

CashFlowPut::~CashFlowPut() 
{
}

double CashFlowPut::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    const double cashFlow = _cashFlow->operator()(path);

    return std::max(0.0, _strike - cashFlow);
}

