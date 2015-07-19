#pragma once

#include "SampleCalculator2.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class PathwiseDeltaCalculator : public SampleCalculator2 {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    PathwiseCalculator(const std::size_t dimension);
    ~PathwiseCalculator();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms) const;

private:
    boost::numeric::ublas::matrix<double> _pathwiseOperator;
            
};

