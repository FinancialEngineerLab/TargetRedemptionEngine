#pragma once

#include "CashFlowCalculator.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowPut : public CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    CashFlowPut(
        const double strike,
        const std::size_t assetIndex,
        const std::size_t maturityIndex);
    virtual ~CashFlowPut();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const double _strike;
    const std::size_t _assetIndex;
    const std::size_t _maturityIndex;

};

