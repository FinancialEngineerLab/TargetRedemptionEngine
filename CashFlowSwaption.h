#pragma once

#include "CashFlowCalculator.h"
#include "CashFlowSwap.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>

class CashFlowSwaption : public CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    CashFlowSwaption(
        const boost::shared_ptr<const CashFlowSwap>& swap);
    virtual ~CashFlowSwaption();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const boost::shared_ptr<const CashFlowSwap> _swap;

};

