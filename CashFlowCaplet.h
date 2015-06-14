#pragma once

#include "CashFlow.h"
#include "Tenor.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowCaplet
    : public CashFlowInterface {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowCaplet(
        const std::size_t cashFlowDateIndex,
        const double strike,
        const boost::shared_ptr<const Tenor>& tenor);
    ~CashFlowCaplet();
    
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
    const CashFlow _cashFlow;
    const double _strike;
    const boost::shared_ptr<const Tenor> _tenor;

};

