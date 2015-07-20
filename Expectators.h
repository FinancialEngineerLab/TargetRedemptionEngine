#pragma once

#include "SampleCalculator.h"
#include "ExpectatorsBase.h"

#include <boost/shared_ptr.hpp>

class Expectators : public ExpectatorsBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    Expectators(
        const boost::shared_ptr<ExpectatorsBase>& next,
        const boost::shared_ptr<const SampleCalculator>& sampleCalculator);
    virtual ~Expectators();

    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms);
    virtual double doExpectation();
        
private:
    const boost::shared_ptr<const SampleCalculator> _sampleCalculator;
            
};

