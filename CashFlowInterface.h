#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlowInterface {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowInterface();
    ~CashFlowInterface();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const = 0;
    virtual std::size_t getCashFlowDateIndex() const = 0;
};

