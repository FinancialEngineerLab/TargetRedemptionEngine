#ifndef CASH_FLOW_TARGET_REDEMPTION_FORWARD_H
#define CASH_FLOW_TARGET_REDEMPTION_FORWARD_H

#include "CashFlowCalculator.h"
#include "TimeIndexManager.h"
#include "SampleTransform.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

class CashFlowTargetRedemptionForward : public CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowTargetRedemptionForward(
        const double strike,
        const double targetLevel,
        const std::vector<double>& discountFactors,
        const TimeIndexManager& excerciseDate,
        const boost::shared_ptr<SampleTransform>& transform);
    virtual ~CashFlowTargetRedemptionForward();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const double _strike;
    const double _targetLevel;
    const std::vector<double> _discountFactors;
    const TimeIndexManager _excerciseDate;
    const boost::shared_ptr<SampleTransform> _transform;
};

#endif