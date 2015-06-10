#pragma once

#include "CashFlow.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class CashFlowDeltaHedge
    : public CashFlow
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    CashFlowDeltaHedge(
        const double strike, const double maturity, 
        const double volatility, const double interestRate, 
        const double dividend,
        const boost::numeric::ublas::vector<double>& discountFactors,
        const std::vector<double>& observedTimes,
        const std::size_t cashFlowDateIndex);
    virtual ~CashFlowDeltaHedge();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
    
private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
    const double _strike;
    const double _maturity;
    const double _volatility;
    const double _interestRate;
    const double _dividend;
    const boost::numeric::ublas::vector<double> _discountFactors;
    const std::vector<double> _observedTimes;

    double calculateDelta(
        const double spot,
        const std::size_t timeIndex) const;

};

