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
        const std::size_t dimension,
        const boost::shared_ptr<const SampleCalculator>& sampleCalculator);
    virtual ~Expectators();

    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms);
    virtual void doExpectation(
        boost::numeric::ublas::vector<double>& result);
        
private:
    const boost::shared_ptr<const SampleCalculator> _sampleCalculator;
    boost::numeric::ublas::vector<double> _cache;
            
};

