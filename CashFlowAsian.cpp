#include "CashFlowAsian.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowAsian::CashFlowAsian(
    const boost::numeric::ublas::vector<double>& observedTimes,
    const boost::shared_ptr<const PayOff>& payOff) 
    :
    CashFlowCalculator(observedTimes),
    _payOff(payOff)
{
}

CashFlowAsian::~CashFlowAsian() 
{
}

void CashFlowAsian::calculateCashFlows(
    const boost::numeric::ublas::matrix<double>& path,
    boost::numeric::ublas::vector<double>& cashFlows) const
{
    boost::numeric::ublas::vector<double> spotAverage(path.size1(), 0.0);

    for (std::size_t timeIndex = 1; timeIndex < path.size2(); ++timeIndex) {
        spotAverage += boost::numeric::ublas::column(path, timeIndex);
    }
    spotAverage /= path.size2() - 1;

    cashFlows[0] = _payOff->payOffFunction(spotAverage);
}

