#pragma once

#include "SampleCalculator.h"
#include "ExpectationBase.h"

#include <boost/shared_ptr.hpp>

class Expectation : public ExpectationBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    Expectation(
        const boost::shared_ptr<const SampleCalculator>& sampleCalculator);
    virtual ~Expectation();

    virtual void addSample(const boost::numeric::ublas::matrix<double>& path);
    virtual double doExpectation();
        
private:
    const boost::shared_ptr<const SampleCalculator> _sampleCalculator;
            
};

