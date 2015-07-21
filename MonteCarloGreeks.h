#pragma once

#include "PathSimulatorBase.h"
#include "PresentValueCalculator.h"
#include "PathwiseOperatorGenerator.h"
#include "ExpectatorBase.h"
#include "RandomGeneratorBase.h"

#include <boost/shared_ptr.hpp>

class MonteCarloGreeks {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MonteCarloGreeks(
        const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
        const boost::shared_ptr<ExpectatorBase>& expectation,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator);
    ~MonteCarloGreeks();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    double simulate(
        const boost::numeric::ublas::vector<double>& spots,
        const std::size_t numberOfSimulations,
        const std::vector<double>& observedTimes,
        const boost::numeric::ublas::vector<double>& discountFactors) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const PathSimulatorBase> _pathSimulator;
    const boost::shared_ptr<ExpectatorBase> _expectation;
    const boost::shared_ptr<PathwiseOperatorGenerator> _generator;
    const boost::shared_ptr<RandomGeneratorBase> _randomGenerator;


};



