#include "Function2DLogInterpolate.h"

/******************************************************************************
 * free funcitions.
 ******************************************************************************/
inline double logarithmicWeight(
    const double x,
    const double lowWeight,
    const double highWeight)
{
    return (log(x/lowWeight)) / (log(highWeight/lowWeight));
}

inline double logarithmicInterpolate(
    const double x,
    const double leftPoint,
    const double rightPoint,
    const double lowWeight,
    const double highWeight)
{
    const double weight = logarithmicWeight(x, lowWeight, highWeight);
    return (1.0 - weight) * leftPoint + weight * rightPoint;
}


/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
Function2DLogInterpolate::Function2DLogInterpolate(
    const boost::numeric::ublas::matrix<double>& strikes, 
    const boost::numeric::ublas::matrix<double>& volatilities,
    const TimeIndexManager& timeIndexManager)
    :
    _strikes(strikes),
    _volatilities(volatilities),
    _timeIndexManager(timeIndexManager)
{
    assert(volatilities.size1() == strikes.size1());
    assert(volatilities.size2() == strikes.size2());
}
Function2DLogInterpolate::~Function2DLogInterpolate() 
{
}


/******************************************************************************
 * operators.
 ******************************************************************************/
double Function2DLogInterpolate::operator()(
    const double time, 
    const double state) const
{
    const std::size_t timeLastIndex = _volatilities.size1() - 1;
    const std::size_t lastIndex = _strikes.size2() - 1;

    int timeIndex = _timeIndexManager.searchIndex(time);
    if (timeIndex < 0) {
        timeIndex = 0;
    } else if (timeIndex > static_cast<int>(timeLastIndex)) {
        timeIndex = timeLastIndex;
    }

    int strikeIndex;
    for (strikeIndex = 0; strikeIndex < static_cast<int>(lastIndex); 
        ++strikeIndex) {
        if (state < _strikes(timeIndex, strikeIndex)) {
            strikeIndex -= 1;
            break;
        }
    }
    if (strikeIndex < 0) {
        strikeIndex = 0;
    } else if (strikeIndex >= static_cast<int>(lastIndex)) {
        strikeIndex = lastIndex - 1;
    }

    return logarithmicInterpolate(state, 
        _volatilities(timeIndex, strikeIndex),
        _volatilities(timeIndex, strikeIndex + 1), 
        _strikes(timeIndex, strikeIndex), 
        _strikes(timeIndex, strikeIndex + 1));
}

