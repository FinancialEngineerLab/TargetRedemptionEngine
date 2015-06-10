#pragma once

#include "PresentValueCalculator.h"
#include "ExpectationBase.h"

class Expectation 
    : public ExpectationBase
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    Expectation(
        const boost::shared_ptr<const PresentValueCalculator>& presentValueCalculator);
    virtual ~Expectation();

    virtual void addSample(const boost::numeric::ublas::matrix<double>& path);
    virtual double doExpectation(const std::size_t numberOfSamples);
        
private:
    const boost::shared_ptr<const PresentValueCalculator> 
        _presentValueCalculator;
            
};

