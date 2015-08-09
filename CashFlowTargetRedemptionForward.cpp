#include "CashFlowTargetRedemptionForward.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowTargetRedemptionForward::CashFlowTargetRedemptionForward(
    const std::size_t numberOfSimulations,
    const double strike,
    const double targetLevel)
    :
    _strike(strike),
    _targetLevel(targetLevel),
    _targets(numberOfSimulations, 0.0)
{
}

CashFlowTargetRedemptionForward::~CashFlowTargetRedemptionForward() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double CashFlowTargetRedemptionForward::operator()(
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

