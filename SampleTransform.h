#pragma once

#include <boost/numeric/ublas/vector.hpp>

class SampleTransform{
public:
    SampleTransform();
    virtual ~SampleTransform();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(const double time, const double state) = 0;
    //TODO: accept multi-dimentional process.
    //virtual boost::numeric::ublas::vector<double>& operator()(
    //        const double time, 
    //        boost::numeric::ublas::vector<double>&  state) = 0;

private:
            
};

