#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlow {
public:
    CashFlow(const std::size_t cashFlowDateIndex);
    virtual ~CashFlow();

    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const = 0;

    inline std::size_t getCashFlowDateIndex() const;
    
private:
    //! tiemIndex is a index at which cash flow occurs.
    const std::size_t _cashFlowDateIndex;
};


inline std::size_t CashFlow::getCashFlowDateIndex() const
{
    return _cashFlowDateIndex;
}
