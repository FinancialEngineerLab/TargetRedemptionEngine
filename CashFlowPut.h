#pragma once

#include <boost/numeric/ublas/vector.hpp>

class CashFlowPut
{
public:
    CashFlowPut(const double strike);
    virtual ~CashFlowPut();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& path) const;
    
private:
    const double _strike;

};

