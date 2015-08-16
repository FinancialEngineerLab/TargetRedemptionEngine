#pragma once

#include "SampleTransform.h"

#include <boost/numeric/ublas/matrix.hpp>

class SampleTransformNull : public SampleTransform {
public:
    SampleTransformNull();
    virtual ~SampleTransformNull();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(const double time, const double state);

private:
            
};

