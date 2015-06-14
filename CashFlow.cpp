#include "CashFlow.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlow::CashFlow(const std::size_t cashFlowDateIndex)
    :
    _cashFlowDateIndex(cashFlowDateIndex)
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
    return 0.0;
}

std::size_t CashFlow::getCashFlowDateIndex() const
{
    return _cashFlowDateIndex;
}

