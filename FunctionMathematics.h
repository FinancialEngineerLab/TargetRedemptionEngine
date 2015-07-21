#pragma once

#include <boost/numeric/ublas/vector.hpp>

class FunctionMathematics {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    FunctionMathematics();
    virtual ~FunctionMathematics();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& x) = 0;
    virtual void calculateDifferential(
        const boost::numeric::ublas::vector<double>& x,
        boost::numeric::ublas::vector<double>& result) = 0;
 
    
private:
            
};

