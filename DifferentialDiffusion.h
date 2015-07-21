#pragma once

#include <boost/multi_array.hpp>
#include <boost/numeric/ublas/vector.hpp>

class DifferentialDiffusion {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    DifferentialDiffusion();
    virtual ~DifferentialDiffusion();

    virtual void calculate(
        const double time,
        const boost::numeric::ublas::vector<double>& states,
        boost::multi_array<double, 3>& result) const = 0;
    
private:
        
};

