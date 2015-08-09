#include "CashFlowTargetRedemptionForward.h"

#include <algorithm>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
CashFlowTargetRedemptionForward::CashFlowTargetRedemptionForward(
    const double strike,
    const double targetLevel,
    const std::vector<double>& discountFactors,
    const TimeIndexManager& excerciseDate,
    const boost::shared_ptr<SampleTransform>& transform)
    :
    _strike(strike),
    _targetLevel(targetLevel),
    _discountFactors(discountFactors),
    _excerciseDate(excerciseDate),
    _transform(transform)
{
}

CashFlowTargetRedemptionForward::~CashFlowTargetRedemptionForward() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double CashFlowTargetRedemptionForward::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    double target = 0.0;
    double presentValue = 0.0;
    for (std::size_t timeIndex = 0; timeIndex < _excerciseDate.size(); 
        ++timeIndex) {
        const std::size_t gridIndex = _excerciseDate.getTimeIndex(timeIndex);
        if (target > _targetLevel) {
            break;
        }
        target += std::max(
            _transform->operator()(path(0, gridIndex)) - _strike, 0.0);
        presentValue += 
            _discountFactors[gridIndex] * 
                (_transform->operator()(path(0, gridIndex)) - _strike);
    }

    return presentValue;
}

