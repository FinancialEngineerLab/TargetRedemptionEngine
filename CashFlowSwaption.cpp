#include "CashFlowSwaption.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowCalculator::CashFlowCalculator(
    const boost::shared_ptr<const CashFlowSwap>& swap)
    :
    _swap(swap)
{
}

CashFlowCalculator::~CashFlowCalculator() 
{
}

double operator()(
    const boost::numeric::ublas::vector<double>& path) const
{
    double cashFlow = _swap->operator()(path);

    return std::max(0.0, cashFlow);
}

