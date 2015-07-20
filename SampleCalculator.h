#pragma once

#include <boost/numeric/ublas/matrix.hpp>

class SampleCalculator{
public:
    SampleCalculator();
    virtual ~SampleCalculator();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void operator()(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms,
        boost::numeric::ublas::vector<double>& result) const = 0;

private:
            
};

