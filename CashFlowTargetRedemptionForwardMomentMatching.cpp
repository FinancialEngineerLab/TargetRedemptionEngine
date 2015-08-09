#include "CashFlowTargetRedemptionForwardMomentMatching.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowTargetRedemptionForwardMomentMatching::
    CashFlowTargetRedemptionForwardMomentMatching(
    const std::size_t numberOfSimulations,
    const double strike,
    const double targetLevel,
    const TimeIndexManager& excerciseDate)
    :
    _strike(strike),
    _targetLevel(targetLevel),
    _targets(numberOfSimulations, 0.0),
    _excerciseDate(excerciseDate)
{
}

CashFlowTargetRedemptionForwardMomentMatching::
    ~CashFlowTargetRedemptionForwardMomentMatching() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double CashFlowTargetRedemptionForwardMomentMatching::operator()(
    const double sampleAtGrid,
    const std::size_t simulationIndex, 
    const std::size_t timeIndex)
{
    if (_targets[simulationIndex] > _targetLevel) {
        return 0.0;
    }

    _targets[simulationIndex] += std::max(sampleAtGrid - _strike, 0.0);

    return sampleAtGrid - _strike;
}

