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
    virtual double operator()(const double x) const;
    virtual void operator()(
        const boost::numeric::ublas::vector<double>& x,
        boost::numeric::ublas::vector<double>& result) const;

private:
            
};

