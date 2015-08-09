#pragma once

#include <boost/numeric/ublas/matrix.hpp>

class CashFlowCalculatorMomentMatching {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    CashFlowCalculatorMomentMatching();
    virtual ~CashFlowCalculatorMomentMatching();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const double sampleAtGrid,
        const std::size_t simulationIndex,
        const std::size_t timeIndex) = 0;
    
private:
};
