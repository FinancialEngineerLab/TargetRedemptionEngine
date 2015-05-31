#include "CashFlowAverage.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowAverage::CashFlowAverage(
    const std::size_t spotIndex,
    const boost::numeric::ublas::vector<double>& observedTimes)
    :
    _spotIndex(spotIndex),
    _observedTimes(observedTimes)
{
}

CashFlowAverage::~CashFlowAverage() 
{
}

double CashFlowAvrage::operator()(
    const boost::numeric::ublas::vector<double>& path) const
{
    const double average = calculateAverage(path);

    return average;
}

double CashFlowAvrage::calculateAverage(
    const boost::numeric::ublas::vector<double>& path) const
{
    double average = 0.0;
    for (std::size_t timeIndex = 0; timeIndex < _observedTimes.size(); ++timeIndex) {
        average += path[_spotIndex][_observedTimes[timeIndex]];
    }

    return average / _observedTimes.size();
}

