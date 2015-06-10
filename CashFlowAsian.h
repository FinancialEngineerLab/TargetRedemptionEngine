#pragma once

#include "CashFlow.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

class CashFlowAsian
    : public CashFlow
{
public:
    CashFlowAsian(
        const std::size_t timeIndex,
        const std::size_t spotIndex,
        const std::vector<std::size_t>& timeIndice);
    virtual ~CashFlowAsian();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const std::size_t _spotIndex;
    const std::vector<std::size_t> _timeIndice;

    double calculateAsian(
        const boost::numeric::ublas::matrix<double>& path) const;
};

