#pragma once

#include <boost/numeric/ublas/vector.hpp>

class SampleTransform{
public:
    SampleTransform();
    virtual ~SampleTransform();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(const double x) const = 0;
    virtual void operator()(
        const boost::numeric::ublas::vector<double>& x,
        boost::numeric::ublas::vector<double>& result) const = 0;

private:
            
};

