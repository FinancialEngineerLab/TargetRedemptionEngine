#pragma once

#include "FunctionMathematics.h"

class FunctionCaplet : public FunctionMathematics {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    FunctionCaplet(
        const double strike,
        const std::size_t dimensionIndex);
    virtual ~FunctionCaplet();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& spot);
    virtual void calculateDifferential(
        const boost::numeric::ublas::vector<double>& spot,
        boost::numeric::ublas::vector<double>& result);
    
private:
    const double _strike;
    const std::size_t _dimensionIndex;            
};

