#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class DifferentialDrift 
{
public:
    DifferentialDrift();
    virtual ~DifferentialDrift();

    virtual void calculate(
        const double time,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& result) = 0;
    
private:
        
};
