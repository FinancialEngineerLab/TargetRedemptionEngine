#pragma once

#include <boost/numeric/ublas/matrix.hpp>

class CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowCalculator();
    ~CashFlowCalculator();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const = 0;
    
private:
};
