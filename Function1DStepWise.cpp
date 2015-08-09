#include "Function1DStepWise.h"

Function1DStepWise::Function1DStepWise(
    const boost::numeric::ublas::vector<double>& steps, 
    const TimeIndexManager& timeIndexManager)
    :
    _steps(steps),
    _timeIndexManager(timeIndexManager)
{

}

Function1DStepWise::~Function1DStepWise()
{

}

/**************************************************************************
 * operators.
 **************************************************************************/
double Function1DStepWise::operator()(const double time) const
{
    const int index = _timeIndexManager.searchIndex(time);
    const std::size_t lastIndex = 
        static_cast<int>(_steps.size()) - 1;

    //out of all intervals.
    if (index < 0) {
        return _steps[0];
    } else if (static_cast<std::size_t>(index) >= lastIndex) {
        return _steps[lastIndex];
    //in a certain interval.
    } else {
        return _steps[index];
    }
}

