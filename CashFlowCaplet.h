#pragma once

#include "CashFlowCalculator.h"
#include "Tenor.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowCaplet : public CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    CashFlowCaplet(
        const double strike,
        const boost::shared_ptr<const Tenor>& tenor);
    virtual ~CashFlowCaplet();
    
    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const double _strike;
    const boost::shared_ptr<const Tenor> _tenor;

};

