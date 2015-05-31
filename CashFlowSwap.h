#pragma once

#include <boost/numeric/ublas/vector.hpp>

class CashFlowCalculator 
{
public:
    CashFlowCalculator();
    virtual ~CashFlowCalculator();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& path) const;
    
private:

};

