#pragma once

#include <boost/numeric/ublas/matrix.hpp>

class SampleCalculator2{
public:
    SampleCalculator2();
    virtual ~SampleCalculator2();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms) const = 0;
private:
            
};

