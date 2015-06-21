#pragma once

#include "CashFlowCalculator.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowCall : public CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowCall(const double strike,
        const std::size_t assetIndex,
        const std::size_t maturityIndex);
    ~CashFlowCall();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const double _strike;
    const std::size_t _assetIndex;
    const std::size_t _maturityIndex;

};

