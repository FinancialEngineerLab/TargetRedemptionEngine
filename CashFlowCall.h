#pragma once

#include <boost/numeric/ublas/vector.hpp>

class CashFlowCall
{
public:
    CashFlowCall(const double strike);
    virtual ~CashFlowCall();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& path) const;
    
private:
    const double _strike;

};

