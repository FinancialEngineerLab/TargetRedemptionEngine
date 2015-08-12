#ifndef FUNCITON_2D_LOG_INTERPOLATE_H
#define FUNCITON_2D_LOG_INTERPOLATE_H

#include "TimeIndexManager.h"

#include <boost/numeric/ublas/matrix.hpp>

class Function2DLogInterpolate {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    Function2DLogInterpolate(
        const boost::numeric::ublas::matrix<double>& strikes, 
        const boost::numeric::ublas::matrix<double>& volatilities,
        const TimeIndexManager& timeIndexManager);
     ~Function2DLogInterpolate();

    /**************************************************************************
     * operators.
     **************************************************************************/
    double operator()(
        const double time, 
        const double state) const;

    double differentialByX(
        const double time, 
        const double state);

    double interpolateIntegral(
        const double time, 
        const double state);
private:
    const boost::numeric::ublas::matrix<double> _strikes;
    const boost::numeric::ublas::matrix<double> _volatilities;
    const TimeIndexManager _timeIndexManager;
        
};


#endif

