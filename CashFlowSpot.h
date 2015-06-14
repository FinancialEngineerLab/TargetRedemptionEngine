#pragma once

#include "CashFlow.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlowSpot 
    : public CashFlowInterface {
public:
    /******************************************************************************
     * Constructers and Destructers.
     ******************************************************************************/
    CashFlowSpot(
        const std::size_t cashFlowDateIndex, 
        const std::size_t maturityIndex, 
        const std::size_t assetIndex);
    virtual ~CashFlowSpot();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    virtual std::size_t getCashFlowDateIndex() const;

private:
    const CashFlow _cashFlow;
    const std::size_t _maturityIndex;
    const std::size_t _assetIndex;
            
};

