#pragma once

#include "CashFlow.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlowSpot 
    : public CashFlow {
public:
    /******************************************************************************
     * Constructers and Destructers.
     ******************************************************************************/
    CashFlowSpot(const std::size_t timeIndex, 
        const std::size_t maturityIndex, const std::size_t assetIndex);
    virtual ~CashFlowSpot();

    double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;

private:
    const std::size_t _maturityIndex;
    const std::size_t _assetIndex;
            
};

