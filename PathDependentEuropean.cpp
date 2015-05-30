#include "PathDependentEuropean.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>

PathDependentEuropean::PathDependentEuropean(
    const boost::numeric::ublas::vector<double>& observedTimes,
    const boost::shared_ptr<const PayOff>& payOff) 
    :
    PathDependent(observedTimes),
    _payOff(payOff)
{
    
}

PathDependentEuropean::~PathDependentEuropean() 
{
}

void PathDependentEuropean::calculateCashFlows(
    const boost::numeric::ublas::matrix<double>& spotsValues,
    boost::numeric::ublas::vector<double>& cashFlows) const
{
    cashFlows[cashFlows.size() - 1] = _payOff->payOffFunction(
        boost::numeric::ublas::column(spotsValues, spotsValues.size2() - 1));
}

