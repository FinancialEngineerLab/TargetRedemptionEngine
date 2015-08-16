#ifndef FUNCITON_2D_LOG_INTERPOLATE_H
#define FUNCITON_2D_LOG_INTERPOLATE_H

#include "TimeIndexManager.h"
#include "FunctionMathematics.h"

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

    double differentialByState(
        const double time, 
        const double state) const;

    double integrateByState(
        const double time, 
        const double state);

    void out() const;

    std::vector<double> getTimeGrid() const;

    std::size_t searchTimeIndex(const double time) const;

private:
    const boost::numeric::ublas::matrix<double> _strikes;
    const boost::numeric::ublas::matrix<double> _volatilities;
    const TimeIndexManager _timeIndexManager;
    //! cache
    boost::numeric::ublas::matrix<double>  _stepIntegral;
        
    /**************************************************************************
     * private functions.
     **************************************************************************/
    double invokeLogarithmicInterpolate(
        const double x,
        const std::size_t timeIndex,
        const std::size_t strikeIndex) const;

    double invokeLogarithmicInterpolateDifferential(
        const double x,
        const std::size_t timeIndex,
        const std::size_t strikeIndex) const;
};


#endif


