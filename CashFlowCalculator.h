#pragma once

#include <boost/numeric/ublas/vector.hpp>

class CashFlowCalculator 
{
public:
    CashFlowCalculator(const boost::numeric::ublas::vector<double>& observedTimes);
    virtual ~CashFlowCalculator();

    virtual void calculateCashFlows(
        const boost::numeric::ublas::matrix<double>& spotValues,
        boost::numeric::ublas::vector<double>& cashFlows) const = 0;
    virtual double calculatePresentValue(
        const boost::numeric::ublas::vector<double>& cashFlows,
        const boost::numeric::ublas::vector<double>& discountFactors) const;
    
private:
    const boost::numeric::ublas::vector<double> _observedTimes;
};
