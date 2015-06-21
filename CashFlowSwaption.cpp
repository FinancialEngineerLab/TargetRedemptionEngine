#include "CashFlowSwaption.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
CashFlowSwaption::CashFlowSwaption(
    const boost::shared_ptr<const CashFlowSwap>& swap)
    :
    _swap(swap)
{
}

CashFlowSwaption::~CashFlowSwaption() 
{
}

/**************************************************************************
 * inherited pure virtual functions.
 **************************************************************************/
double CashFlowSwaption::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    double cashFlow = _swap->operator()(path);

    return std::max(0.0, cashFlow);
}

