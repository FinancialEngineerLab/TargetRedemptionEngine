#pragma once

#include "CashFlow.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowCall
    : public CashFlow
{
public:
    CashFlowCall(const double strike,
        const boost::shared_ptr<const CashFlow> cashFlow);
    virtual ~CashFlowCall();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const double _strike;
    const boost::shared_ptr<const CashFlow> _cashFlow;

};

