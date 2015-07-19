#pragma once

#include "CashFlow.h"
#include "SampleCalculator.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class PresentValueCalculator : public SampleCalculator {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    PresentValueCalculator(
        const boost::shared_ptr<const CashFlow>& cashFlow,
        const boost::numeric::ublas::vector<double>& discountFactors);
    ~PresentValueCalculator();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;

private:
    const boost::shared_ptr<const CashFlow> _cashFlow;
    const boost::numeric::ublas::vector<double> _discountFactors;
    const std::vector<double> sumOfDiscountFactors;
            
};

