#include "CashFlowAverage.h"


/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowAverage::CashFlowAverage(
    const std::size_t timeIndex,
    const std::size_t spotIndex,
    const std::vector<std::size_t>& timeIndice)
    :
     CashFlow(timeIndex),
    _spotIndex(spotIndex),
    _timeIndice(timeIndice)
{
}

CashFlowAverage::~CashFlowAverage() 
{
}

double CashFlowAverage::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    const double average = calculateAverage(path);

    return average;
}

double CashFlowAverage::calculateAverage(
    const boost::numeric::ublas::matrix<double>& path) const
{
    double average = 0.0;
    for (std::size_t timeIndex = 0; timeIndex < _timeIndice.size(); ++timeIndex) {
        average += path(_spotIndex, _timeIndice[timeIndex]);
    }

    return average / _timeIndice.size();
}

