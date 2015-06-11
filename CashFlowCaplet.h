#pragma once

#include "CashFlow.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowCaplet
    : public CashFlow {
public:
    CashFlowCaplet(const double strike,
        const boost::shared_ptr<const CashFlow> cashFlow,
        const std::size_t assetIndex);
    virtual ~CashFlowCaplet();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const double _strike;
    const boost::shared_ptr<const CashFlow> _cashFlow;
    const std::size_t assetIndex;

};

