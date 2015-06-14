#pragma once

#include "CashFlowInterface.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlow 
    : public CashFlowInterface {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlow(const std::size_t cashFlowDateIndex);
    virtual ~CashFlow();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    virtual std::size_t getCashFlowDateIndex() const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    //! timeIndex is a index at which cash flow occurs.
    const std::size_t _cashFlowDateIndex;
};


