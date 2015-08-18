#pragma once

#include "CashFlowMomentMatching.h"
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
        const boost::shared_ptr<CashFlowMomentMatching>& cashFlow,
        const std::vector<double>& discountFactors,
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
    const boost::shared_ptr<CashFlowMomentMatching> _cashFlow;
    const std::vector<double> _discountFactors;
            
};
