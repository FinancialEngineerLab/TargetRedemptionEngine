#pragma once

#include "PayOff.h"

class PayOffCaplet 
    : public PayOff
{
public:
    PayOffCaplet(const double strike, const std::size_t maturityIndex,
        const boost::numeric::ublas::vector<double>& tenor,
        const boost::numeric::ublas::vector<double>& discountFactors);
    virtual ~PayOffCaplet();

    virtual double payOffFunction(
        const boost::numeric::ublas::vector<double>& spots) const;
    
private:
    const double _strike;            
    const std::size_t _maturityIndex;
    const boost::numeric::ublas::vector<double> _tenor;
    const boost::numeric::ublas::vector<double> _discountFactors;
};

