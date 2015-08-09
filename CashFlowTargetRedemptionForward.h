#ifndef CASH_FLOW_TARGET_REDEMPTION_FORWARD_H
#define CASH_FLOW_TARGET_REDEMPTION_FORWARD_H

#include "CashFlowCalculatorMomentMatching.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

class CashFlowTargetRedemptionForward : public CashFlowCalculatorMomentMatching {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowTargetRedemptionForward(
        const std::size_t numberOfSimulations,
        const double strike,
        const double targetLevel);
    virtual ~CashFlowTargetRedemptionForward();

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
};

#endif
