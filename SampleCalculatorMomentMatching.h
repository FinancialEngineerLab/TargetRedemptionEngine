#pragma once

#include <boost/numeric/ublas/matrix.hpp>

class SampleCalculatorMomentMatching {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    SampleCalculatorMomentMatching();
    virtual ~SampleCalculatorMomentMatching();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const double sampleAtGrid,
        const std::size_t simulationIndex,
        const std::size_t timeIndex) = 0;

private:
            
};

