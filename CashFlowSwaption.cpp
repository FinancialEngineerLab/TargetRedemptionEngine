#include "CashFlowSwaption.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowSwaption::CashFlowSwaption(
    const std::size_t timeIndex,
    const boost::shared_ptr<const CashFlowSwap>& swap)
    :
    CashFlow(timeIndex),
    _swap(swap)
{
}

CashFlowSwaption::~CashFlowSwaption() 
{
}

double CashFlowSwaption::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    double cashFlow = _swap->operator()(path);

    return std::max(0.0, cashFlow);
}

