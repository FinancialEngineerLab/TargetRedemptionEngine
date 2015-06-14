#include "CashFlowCall.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowCall::CashFlowCall(
    const double strike,
    const boost::shared_ptr<const CashFlowInterface> cashFlow)
    :
    _strike(strike),
    _cashFlow(cashFlow)
{
}

CashFlowCall::~CashFlowCall() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double CashFlowCall::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    const double cashFlow = _cashFlow->operator()(path);

    return std::max(0.0, cashFlow - _strike);
}

std::size_t CashFlowCall::getCashFlowDateIndex() const
{
    return _cashFlow->getCashFlowDateIndex();
}

