#pragma once

#include "CashFlow.h"
#include "CashFlowSwap.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>

class CashFlowSwaption 
    : public CashFlow {
public:
    CashFlowSwaption(const std::size_t timeIndex, 
        const boost::shared_ptr<const CashFlowSwap>& swap);
    virtual ~CashFlowSwaption();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const boost::shared_ptr<const CashFlowSwap> _swap;

};

