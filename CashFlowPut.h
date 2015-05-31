#pragma once

#include "CashFlow.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowPut
    : public CashFlow
{
public:
    CashFlowPut(const std::size_t timeIndex, const double strike,
        const boost::shared_ptr<const CashFlow> cashFlow);
    virtual ~CashFlowPut();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const double _strike;
    const boost::shared_ptr<const CashFlow> _cashFlow;

};

