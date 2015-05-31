#include "CashFlowEuropean.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>

CashFlowEuropean::CashFlowEuropean(
    const boost::numeric::ublas::vector<double>& observedTimes,
    const boost::shared_ptr<const PayOff>& payOff) 
    :
    CashFlowCalculator(observedTimes),
    _payOff(payOff)
{
    
}

CashFlowEuropean::~CashFlowEuropean() 
{
}

void CashFlowEuropean::calculateCashFlows(
    const boost::numeric::ublas::matrix<double>& path,
    boost::numeric::ublas::vector<double>& cashFlows) const
{
    cashFlows[cashFlows.size() - 1] = _payOff->payOffFunction(
        boost::numeric::ublas::column(path, path.size2() - 1));
}

