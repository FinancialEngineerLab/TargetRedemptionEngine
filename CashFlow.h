#pragma once

#include "CashFlowCalculator.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlow : public CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    CashFlow(
        const boost::shared_ptr<const CashFlowCalculator> calculator,
        const std::size_t paymentDateIndex);
    virtual ~CashFlow();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;

    /**************************************************************************
     * member functions.
     **************************************************************************/
    std::size_t getPaymentDateIndex() const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const CashFlowCalculator> _calculator;
    //! paymentDateIndex is a index at which cash flow occurs.
    const std::size_t _paymentDateIndex;
};


