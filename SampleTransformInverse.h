#pragma once

#include <boost/numeric/ublas/vector.hpp>

class SampleTransformInverse{
public:
    SampleTransformInverse(
        Function2DLogInterpolate& functor);
    virtual ~SampleTransformInverse();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(const double x) const = 0;
    virtual void operator()(
        const boost::numeric::ublas::vector<double>& x,
        boost::numeric::ublas::vector<double>& result) const = 0;

private:
    boost::numeric::ublas::vector<double> _map;
    Function2DLogInterpolate& _functor;
};

