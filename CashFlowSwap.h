#pragma once

#include "CashFlow.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlowSwap 
    : public CashFlowInterface {
public:
    CashFlowSwap(
        const std::vector<double>& observedTimes,
        const std::vector<std::size_t>& tenorToTime,
        const std::vector<std::size_t>& tenorToAsset,
        const double strike);
    virtual ~CashFlowSwap();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    const CashFlow _cashFlow;
    const std::vector<double> _observedTimes;
    const std::vector<std::size_t> _tenorToTime;
    const std::vector<std::size_t> _tenorToAsset;
    const double _strike;

};

