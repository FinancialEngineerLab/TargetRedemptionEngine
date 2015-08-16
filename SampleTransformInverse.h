#pragma once

#include "SampleTransform.h"
#include "Function2DLogInterpolate.h"

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>

class SampleTransformInverse : public SampleTransform {
public:
    SampleTransformInverse(
        Function2DLogInterpolate& function2D,
        const double from,
        const double to,
        const std::size_t numberOfPartitions);
    virtual ~SampleTransformInverse();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(const double time, const double state);

private:
    Function2DLogInterpolate _function2D;
    const double _from;
    const double _to;
    const double _stepSize;
    const std::vector<double> _timeGrid;
    boost::numeric::ublas::matrix<double> _map;

    /**************************************************************************
     * private functions.
     **************************************************************************/
    inline std::size_t getStateIndex(const double state);
     
};

