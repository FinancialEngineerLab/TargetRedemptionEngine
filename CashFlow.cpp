#include "CashFlow.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
CashFlow::CashFlow(
    const boost::shared_ptr<const CashFlowCalculator> calculator,
    const std::size_t paymentDateIndex)
    :
    _calculator(calculator),
    _paymentDateIndex(paymentDateIndex)
{
}

CashFlow::~CashFlow() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double CashFlow::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    return _calculator->operator()(path);
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
std::size_t CashFlow::getPaymentDateIndex() const
{
    return _paymentDateIndex;
}

