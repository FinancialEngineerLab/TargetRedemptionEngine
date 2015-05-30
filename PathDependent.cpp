#include "PathDependent.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PathDependent::PathDependent(
    const boost::numeric::ublas::vector<double>& observedTimes) 
    :
    _observedTimes(observedTimes)
{
    
}

PathDependent::~PathDependent() 
{
}

double PathDependent::calculatePresentValue(
    const boost::numeric::ublas::vector<double>& cashFlows,
    const boost::numeric::ublas::vector<double>& discountFactors) const
{
    double presentValue = 0.0;  

    for (std::size_t timeIndex = 0; timeIndex < cashFlows.size(); ++timeIndex) {
        presentValue += cashFlows[timeIndex] * discountFactors[timeIndex];
    }

    return presentValue;
}
