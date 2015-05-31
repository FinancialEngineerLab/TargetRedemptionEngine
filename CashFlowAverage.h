#pragma once

#include <boost/numeric/ublas/vector.hpp>

class CashFlowAverage 
{
public:
    CashFlowAverage(
        const std::size_t spotIndex,
        const boost::numeric::ublas::vector<double>& observedTimes);
    virtual ~CashFlowAverage();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& path) const;
    
private:
    const std::size_t _spotIndex;
    const boost::numeric::ublas::vector<double>& _observedTimes;

};

