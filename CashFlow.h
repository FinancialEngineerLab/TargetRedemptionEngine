#pragma once

#include <boost/numeric/ublas/vector.hpp>

class CashFlow
{
public:
    CashFlow(const std::size_t timeIndex);
    virtual ~CashFlow();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& path) const = 0;

    inline std::size_t getTimeIndex();
    
private:
    //! tiemIndex is a index at which cash flow occurs.
    const std::size_t _timeIndex;
};


inline std::size_t CashFlow::getTimeIndex()
{
    return _timeIndex;
}
