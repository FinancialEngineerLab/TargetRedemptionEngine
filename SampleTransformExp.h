#pragma once

#include "SampleTransform.h"

#include <boost/numeric/ublas/matrix.hpp>

class SampleTransformExp : public SampleTransform {
public:
    SampleTransformExp();
    virtual ~SampleTransformExp();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(const double time, const double state);

private:
            
};

