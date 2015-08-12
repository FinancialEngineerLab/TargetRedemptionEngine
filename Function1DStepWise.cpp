#include "Function1DStepWise.h"


/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
Function1DStepWise::Function1DStepWise(
    const boost::numeric::ublas::vector<double>& steps, 
    const TimeIndexManager& timeIndexManager)
    :
    _steps(steps),
    _timeIndexManager(timeIndexManager)
{
    assert(_steps.size() == _timeIndexManager.size() + 1);
}

Function1DStepWise::~Function1DStepWise()
{

}

/**************************************************************************
 * operators.
 **************************************************************************/
double Function1DStepWise::operator()(const double time) const
{
    const std::size_t index = _timeIndexManager.searchIndex(time);
    return _steps[index];
}


/******************************************************************************
 * member functions.
 ******************************************************************************/
double Function1DStepWise::integral(
    const double from,
    const double to) const
{
    double sum = 0.0;
    const std::size_t startIndex = _timeIndexManager.searchIndex(from);
    const std::size_t endIndex = _timeIndexManager.searchIndex(to);

    std::cout << startIndex << std::endl;
    std::cout << endIndex << std::endl;
    if (startIndex == endIndex) {
        return (to - from) * _steps[startIndex];
    } else {
        sum += (_timeIndexManager[startIndex] - from) * _steps[startIndex];
        for (std::size_t timeIndex = startIndex; timeIndex < endIndex - 2; ++timeIndex) {
            sum += (_timeIndexManager[timeIndex + 1] -
                _timeIndexManager[timeIndex]) * _steps[timeIndex];
        }
        sum += (to - _timeIndexManager[endIndex - 1]) * _steps[endIndex];
    }

    return sum;
}


