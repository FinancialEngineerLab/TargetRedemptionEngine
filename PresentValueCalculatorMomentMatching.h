#pragma once

#include "CashFlowCalculatorMomentMatching.h"
#include "SampleCalculatorMomentMatching.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class PresentValueCalculatorMomentMatching : 
    public SampleCalculatorMomentMatching {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    PresentValueCalculatorMomentMatching(
        const boost::shared_ptr<CashFlowCalculatorMomentMatching>& cashFlow,
        const boost::numeric::ublas::vector<double>& discountFactors,
        const std::size_t numberOfSimulations);
    ~PresentValueCalculatorMomentMatching();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const double sampleAtGrid,
        const std::size_t simulationIndex,
        const std::size_t timeIndex);

private:
    const boost::shared_ptr<CashFlowCalculatorMomentMatching> _cashFlow;
    const boost::numeric::ublas::vector<double> _discountFactors;
            
};

