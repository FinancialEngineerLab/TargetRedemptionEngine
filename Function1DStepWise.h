#ifndef FUNCTION_1D_STEP_WISE_H
#define FUNCTION_1D_STEP_WISE_H

#include "TimeIndexManager.h"

#include <boost/numeric/ublas/vector.hpp>

class Function1DStepWise {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    Function1DStepWise(
    const boost::numeric::ublas::vector<double>& steps, 
    const TimeIndexManager& timeIndexManager);
     ~Function1DStepWise();

    /**************************************************************************
     * operators.
     **************************************************************************/
    double operator()(const double time) const;

    double integral(
        const double from,
        const double to) const;
private:
    //! the length of steps is _timeIndexManager.size()+1, say, lastIndex.
    //! steps[0] is the value of the function in (-inf, _timeIndexManager[0]].
    //! steps[lastIndx] is the value of the function 
    //! in (_timeIndexManager[lastIndex-1], +inf).
    const boost::numeric::ublas::vector<double> _steps;
    const TimeIndexManager _timeIndexManager;
        
};

#endif

