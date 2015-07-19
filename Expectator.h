#pragma once

#include "SampleCalculator2.h"
#include "ExpectatorBase.h"

#include <boost/shared_ptr.hpp>

class Expectator : public ExpectatorBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    Expectator(
        const boost::shared_ptr<ExpectatorBase>& next,
        const boost::shared_ptr<const SampleCalculator2>& sampleCalculator);
    virtual ~Expectator();

    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms);
    virtual double doExpectation();
        
private:
    const boost::shared_ptr<const SampleCalculator2> _sampleCalculator;
            
};

