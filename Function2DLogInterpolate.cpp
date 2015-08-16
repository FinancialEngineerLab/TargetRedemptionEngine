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

inline double Function2DLogInterpolate::invokeLogarithmicInterpolate(
    const double x,
    const std::size_t timeIndex,
    const std::size_t strikeIndex) const
{
    return logarithmicInterpolate(x,
        _volatilities(timeIndex, strikeIndex - 1),
        _volatilities(timeIndex, strikeIndex),
        _strikes(timeIndex, strikeIndex - 1),
        _strikes(timeIndex, strikeIndex));
}

double Function2DLogInterpolate::invokeLogarithmicInterpolateDifferential(
    const double x,
    const std::size_t timeIndex,
    const std::size_t strikeIndex) const
{
    
    const double B = 1.0 / 
        log(_strikes(timeIndex, strikeIndex)/_strikes(timeIndex, strikeIndex-1));
    return (_volatilities(timeIndex, strikeIndex) 
        - _volatilities(timeIndex, strikeIndex - 1)) * B / x;
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
    _timeIndexManager(timeIndexManager),
    _stepIntegral(timeIndexManager.size(), _volatilities.size2() + 1)
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

    //calculate integral between each steps.
    for (std::size_t timeIndex = 0; timeIndex < timeIndexManager.size(); 
        ++timeIndex) {
        _stepIntegral(timeIndex, 0) = 0;
        _stepIntegral(timeIndex, 1) =  
            _strikes(timeIndex, 1) / _volatilities(timeIndex, 1);
        for (std::size_t stateIndex = 0; stateIndex < volatilities.size2() - 2; 
            ++stateIndex) {
            const double integral = logarithmicIntegralStep(
                _strikes(timeIndex, stateIndex + 2),
                _strikes(timeIndex, stateIndex + 1),
                _strikes(timeIndex, stateIndex + 2),
                _volatilities(timeIndex, stateIndex + 1),
                _volatilities(timeIndex, stateIndex + 2));

            _stepIntegral(timeIndex, stateIndex + 2) =
                _stepIntegral(timeIndex, stateIndex) + integral;
        }
    }
}

Function2DLogInterpolate::~Function2DLogInterpolate() 
{
}

void Function2DLogInterpolate::out() const
{
    std::cout << "out" << std::endl;
    for (std::size_t row = 0; row < _strikes.size1(); ++row) {
        for (std::size_t column = 0; column < _strikes.size2(); ++column) {
            std::cout << _strikes(row, column) << " ";
        }
        std::cout << std::endl;
    }
}


/******************************************************************************
 * operators.
 ******************************************************************************/
double Function2DLogInterpolate::operator()(
    const double time, 
    const double state) const
{
    const std::size_t timeIndex = searchTimeIndex(time);

    std::size_t strikeIndex = 0;
    const std::size_t lastIndex = _strikes.size2() - 1;

    for (strikeIndex = 0; strikeIndex < _strikes.size2(); ++strikeIndex) {
        if (state < _strikes(timeIndex, strikeIndex)) {
            break;
        }
    }
    //out
    if (strikeIndex == 0) {
        const double interpolate = logarithmicInterpolate(state, 
            _volatilities(timeIndex, 0),
            _volatilities(timeIndex, 1),
            _strikes(timeIndex, 0),
            _strikes(timeIndex, 1));
        return std::max(interpolate, _volatilities(timeIndex, 0));
    } else if (strikeIndex == _strikes.size2()) {
        const double interpolate = logarithmicInterpolate(state, 
            _volatilities(timeIndex, lastIndex - 1),
            _volatilities(timeIndex, lastIndex),
            _strikes(timeIndex, lastIndex - 1),
            _strikes(timeIndex, lastIndex));
        return std::max(interpolate, _volatilities(timeIndex, lastIndex));
    //inside
    } else {
        return logarithmicInterpolate(state, 
            _volatilities(timeIndex, strikeIndex - 1),
            _volatilities(timeIndex, strikeIndex), 
            _strikes(timeIndex, strikeIndex - 1), 
            _strikes(timeIndex, strikeIndex));
    }
}

//integrate f(t, x) w.r.t. x from 0 to state
double Function2DLogInterpolate::integrateByState(
    const double time, 
    const double state) 
{
    const std::size_t timeIndex = searchTimeIndex(time);
    std::size_t strikeIndex = 0;

    //conditioned by state value
    for (strikeIndex = 0; strikeIndex < _strikes.size2(); ++strikeIndex) {
        if (state < _strikes(timeIndex, strikeIndex)) {
            break;
        }
    }
    //before
    //if constant extrapolation, then 0
    if (strikeIndex == 0) {
        const double A = _volatilities(timeIndex, strikeIndex);
        return state / A;
//    //if constant extrapolation, then 0
//    } else if (strikeIndex == _strikes.size2()) {
//        //TODO:need to check
//        const double A = 1.0;
//        return A * state;
    } else {
        const double D = log(_strikes(timeIndex, strikeIndex)
            /_strikes(timeIndex, strikeIndex - 1)) ;
        const double integral =  D * logarithmicIntegralStep(
            state,
            _strikes(timeIndex, strikeIndex - 1),
            _strikes(timeIndex, strikeIndex),
            _volatilities(timeIndex, strikeIndex - 1),
            _volatilities(timeIndex, strikeIndex));

        return integral + _stepIntegral(timeIndex, strikeIndex);
    }

}


//implement at 2DFunction
double Function2DLogInterpolate::differentialByState(
    const double time, 
    const double state) const
{
    const std::size_t timeIndex = searchTimeIndex(time);
    std::size_t strikeIndex = 0;

    //conditioned by state value
    const std::size_t lastIndex = _strikes.size2() - 1;
    for (strikeIndex = 0; strikeIndex < _strikes.size2(); ++strikeIndex) {
        if (state < _strikes(timeIndex, strikeIndex)) {
            break;
        }
    }

    //before
    //if constant extrapolation, then 0
    if (strikeIndex == 0) {
        const double interpolate = invokeLogarithmicInterpolate(
            state, timeIndex, 1);
        if (interpolate > _volatilities(timeIndex, 0)) {
            //return invokeLogarithmicInterpolateDifferential(state, timeIndex, 1);
        }
        return 0.0;
    //if constant extrapolation, then 0
    } else if (strikeIndex == _strikes.size2()) {
        const double interpolate = invokeLogarithmicInterpolate(
            state, timeIndex, lastIndex);
        if (interpolate > _volatilities(timeIndex, lastIndex - 1)) {
            return invokeLogarithmicInterpolateDifferential(
                state, timeIndex, lastIndex);
        }
        return 0.0;
    } else {
        return invokeLogarithmicInterpolateDifferential(
                state, timeIndex, strikeIndex);
    }

}


std::vector<double> Function2DLogInterpolate::getTimeGrid() const
{
    return _timeIndexManager.getTimeGrid();
}

std::size_t Function2DLogInterpolate::searchTimeIndex(const double time) const
{
    const std::size_t timeLastIndex = _timeIndexManager.size();
    std::size_t timeIndex = _timeIndexManager.searchIndex(time);

    if (timeIndex == timeLastIndex) {
        return timeIndex - 1;
    }

    return timeIndex;

}

