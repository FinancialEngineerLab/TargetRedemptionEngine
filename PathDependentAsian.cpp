#include "PathDependentAsian.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

PathDependentAsian::PathDependentAsian(
    const boost::numeric::ublas::vector<double>& observedTimes,
    const boost::shared_ptr<const PayOff>& payOff) 
    :
    PathDependent(observedTimes),
    _payOff(payOff)
{
    
}

PathDependentAsian::~PathDependentAsian() 
{
}

void PathDependentAsian::calculateCashFlows(
    const boost::numeric::ublas::matrix<double>& spotsValues,
    boost::numeric::ublas::vector<double>& cashFlows) const
{
    boost::numeric::ublas::vector<double> spotAverage(spotsValues.size1(), 0.0);

    for (std::size_t timeIndex = 1; timeIndex < spotsValues.size2(); ++timeIndex) {
        spotAverage += boost::numeric::ublas::column(spotsValues, timeIndex);
    }
    spotAverage /= spotsValues.size2() - 1;

    cashFlows[0] = _payOff->payOffFunction(spotAverage);
}

