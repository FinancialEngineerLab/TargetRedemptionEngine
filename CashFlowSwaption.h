#pragma once

#include <boost/numeric/ublas/vector.hpp>

class CashFlowCalculator 
{
public:
    CashFlowCalculator(const boost::shared_ptr<const CashFlowSwap>& swap);
    virtual ~CashFlowCalculator();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& path) const;
    
private:
    const boost::shared_ptr<const CashFlowSwap>& _swap;

};

