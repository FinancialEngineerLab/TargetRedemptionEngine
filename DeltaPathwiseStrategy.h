#pragma once

#include "DeltaStrategy.h"
#include "SampleCalculator.h"
#include "PathSimulator.h"
#include "RandomGeneratorBase.h"
#include "PathwiseOperatorGenerator.h"

#include <boost/shared_ptr.hpp>

class DeltaPathwiseStrategy : public DeltaStrategy {
public:
    DeltaPathwiseStrategy(
        const boost::shared_ptr<const SampleCalculator>& sampleCalculator,
        const boost::shared_ptr<const PathSimulator>& pathSimulator,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator,
        const boost::shared_ptr<PathwiseOperatorGenerator>& generator);
    virtual ~DeltaPathwiseStrategy();

    virtual double calculate(
        boost::numeric::ublas::vector<double>& delta,
        const std::vector<double> observedTimes,
        const std::size_t numberOfSimulations);
    
private:
    const boost::shared_ptr<const SampleCalculator> _sampleCalculator;
    const boost::shared_ptr<const PathSimulator> _pathSimulator;
    const boost::shared_ptr<RandomGeneratorBase> _randomGenerator;
    const boost::shared_ptr<PathwiseOperatorGenerator> _generator;
            
};

