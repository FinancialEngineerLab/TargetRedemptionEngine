#pragma once

#include "CashFlow.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

class CashFlowAsian : public CashFlowCalculator {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowAsian(
        const std::size_t spotIndex,
        const std::vector<std::size_t>& timeIndice);
    ~CashFlowAsian();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const std::size_t _spotIndex;
    const std::vector<std::size_t> _timeIndice;

    /**************************************************************************
     * private functions.
     **************************************************************************/
    double calculateAverage(
        const boost::numeric::ublas::matrix<double>& path) const;
};

