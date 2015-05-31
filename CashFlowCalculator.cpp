#include "CashFlowCalculator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowCalculator::CashFlowCalculator(
    const boost::numeric::ublas::vector<double>& observedTimes) 
    :
    _observedTimes(observedTimes)
{
    
}

CashFlowCalculator::~CashFlowCalculator() 
{
}

double CashFlowCalculator::calculatePresentValue(
    const boost::numeric::ublas::vector<double>& cashFlows,
    const boost::numeric::ublas::vector<double>& discountFactors) const
{
    double presentValue = 0.0;  

    for (std::size_t timeIndex = 0; timeIndex < cashFlows.size(); ++timeIndex) {
        presentValue += cashFlows[timeIndex] * discountFactors[timeIndex];
    }

    return presentValue;
}
