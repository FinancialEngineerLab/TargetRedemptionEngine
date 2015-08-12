#include "Function2DLogInterpolate.h"
#include "utilities.h"

#include <boost/numeric/ublas/io.hpp>

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
    for (std::size_t row = 0; row < _strikes.size1(); ++row) {
        for (std::size_t column = 0; column < _strikes.size2(); ++column) {
            std::cout << _strikes(row, column) << " ";
        }
        std::cout << std::endl;
    }
    for (std::size_t row = 0; row < _volatilities.size1(); ++row) {
        for (std::size_t column = 0; column < _volatilities.size2(); ++column) {
            std::cout << _volatilities(row, column) << " ";
        }
        std::cout << std::endl;
    }
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
    const std::size_t lastIndex = _strikes.size2() - 1;
    const std::size_t timeLastIndex = _timeIndexManager.size();

    std::size_t timeIndex = _timeIndexManager.searchIndex(time);

    std::size_t strikeIndex = 0;
    if (timeIndex == timeLastIndex) {
        timeIndex -= 1;
    }
    for (strikeIndex = 0; strikeIndex < _strikes.size2(); ++strikeIndex) {
        if (state < _strikes(timeIndex, strikeIndex)) {
            break;
        }
    }
    
    //before
    if (strikeIndex == 0) {
        return logarithmicInterpolate(state, 
            _volatilities(timeIndex, strikeIndex),
            _volatilities(timeIndex, strikeIndex + 1), 
            _strikes(timeIndex, strikeIndex), 
            _strikes(timeIndex, strikeIndex + 1));
    } else if (strikeIndex == _strikes.size2()) {
        return logarithmicInterpolate(state, 
            _volatilities(timeIndex, lastIndex - 1),
            _volatilities(timeIndex, lastIndex), 
            _strikes(timeIndex, lastIndex - 1), 
            _strikes(timeIndex, lastIndex));

    } else {
        return logarithmicInterpolate(state, 
            _volatilities(timeIndex, strikeIndex - 1),
            _volatilities(timeIndex, strikeIndex), 
            _strikes(timeIndex, strikeIndex - 1), 
            _strikes(timeIndex, strikeIndex));
    }


}

//implemnt in 2DFunction
double Function2DLogInterpolate::interpolateIntegral(
    const double time, 
    const double state) 
{
    //conditioned by state value
    const std::size_t timeLastIndex = _timeIndexManager.size();

    std::size_t timeIndex = _timeIndexManager.searchIndex(time);

    std::size_t strikeIndex = 0;
    if (timeIndex == timeLastIndex) {
        timeIndex -= 1;
    }
    for (strikeIndex = 0; strikeIndex < _strikes.size2(); ++strikeIndex) {
        if (state < _strikes(timeIndex, strikeIndex)) {
            break;
        }
    }

    //before
    //if constant extrapolation, then 0
    if (strikeIndex == 0) {
        //TODO
        const double A = 1.0;
        return A * state;
    //if constant extrapolation, then 0
    } else if (strikeIndex == _strikes.size2()) {
        //TODO
        const double A = 1.0;
        return A * state;
    } else {
        const double D = log(_strikes(timeIndex, strikeIndex)/_strikes(timeIndex, strikeIndex - 1)) ;
        const double A = D * _volatilities(timeIndex, strikeIndex - 1);
        const double B = (_volatilities(timeIndex, strikeIndex) - _volatilities(timeIndex, strikeIndex - 1));
        const double C = _volatilities(timeIndex, strikeIndex - 1);
        const double x = exp(A) * pow(state/C, B);
        return D * exp(1.0/B) * logarithmicIntegral(x);
    }

}

//implement at 2DFunction
double Function2DLogInterpolate::differentialByX(
    const double time, 
    const double state)
{
    //conditioned by state value
    const std::size_t timeLastIndex = _timeIndexManager.size();

    std::size_t timeIndex = _timeIndexManager.searchIndex(time);

    std::size_t strikeIndex = 0;
    if (timeIndex == timeLastIndex) {
        timeIndex -= 1;
    }
    for (strikeIndex = 0; strikeIndex < _strikes.size2(); ++strikeIndex) {
        if (state < _strikes(timeIndex, strikeIndex)) {
            break;
        }
    }

    //before
    //if constant extrapolation, then 0
    if (strikeIndex == 0) {
        //const double B = 1.0 / log(_strike(timeIndex, 1)/_strikes(timeIndex, 0));
        //return (_volatilities(timeIndex, 1) - _volatilities(timeIndex, 0)) * B/state;
        return 0.0;
    //if constant extrapolation, then 0
    } else if (strikeIndex == _strikes.size2()) {
        //const double B = 1.0 / log(_strike(timeIndex, lastIndex)/_strikes(timeIndex, lastIndex - 1));
        //return (_volatilities(timeIndex, lastIndex) - _volatilities(timeIndex, lastIndex - 1)) * B/state;
        return 0.0;
    } else {
        const double B = 1.0 / log(_strikes(timeIndex, strikeIndex)/_strikes(timeIndex, strikeIndex-1));
        return (_volatilities(timeIndex, strikeIndex) - _volatilities(timeIndex, strikeIndex - 1)) * B/state;
    }

}

