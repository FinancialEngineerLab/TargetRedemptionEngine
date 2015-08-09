#ifndef CASH_FLOW_TARGET_REDEMPTION_FORWARD_MOMENT_MATCHING_H
#define CASH_FLOW_TARGET_REDEMPTION_FORWARD_MOMENT_MATCHING_H

#include "CashFlowCalculatorMomentMatching.h"
#include "TimeIndexManager.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

class CashFlowTargetRedemptionForwardMomentMatching : 
    public CashFlowCalculatorMomentMatching {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowTargetRedemptionForwardMomentMatching(
        const std::size_t numberOfSimulations,
        const double strike,
        const double targetLevel,
        const TimeIndexManager& excerciseDate);
    virtual ~CashFlowTargetRedemptionForwardMomentMatching();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const double sampleAtGrid,
        const std::size_t simulationIndex,
        const std::size_t timeIndex);
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const double _strike;
    const double _targetLevel;
    std::vector<double> _targets;
    const TimeIndexManager _excerciseDate;
};

#endif
