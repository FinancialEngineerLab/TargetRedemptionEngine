#ifndef FUNCTION_1D_STEP_WISEP_H
#define FUNCTION_1D_STEP_WISEP_H

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
private:
    const boost::numeric::ublas::vector<double> _steps;
    const TimeIndexManager _timeIndexManager;
        
};

#endif

