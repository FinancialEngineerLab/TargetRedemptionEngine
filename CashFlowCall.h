#pragma once

#include "CashFlowInterface.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowCall
    : public CashFlowInterface {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowCall(const double strike,
        const boost::shared_ptr<const CashFlowInterface> cashFlow);
    ~CashFlowCall();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    virtual std::size_t getCashFlowDateIndex() const;
    
private:
    const double _strike;
    const boost::shared_ptr<const CashFlowInterface> _cashFlow;

};

