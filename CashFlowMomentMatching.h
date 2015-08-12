#pragma once

#include "CashFlowCalculatorMomentMatching.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlowMomentMatching : public CashFlowCalculatorMomentMatching {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    CashFlowMomentMatching(
        const boost::shared_ptr<CashFlowCalculatorMomentMatching> calculator);
    virtual ~CashFlowMomentMatching();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const double sampleAtGrid,
        const std::size_t simulationIndex,
        const std::size_t timeIndex);
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<CashFlowCalculatorMomentMatching> _calculator;
};


