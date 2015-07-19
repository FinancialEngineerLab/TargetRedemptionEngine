#pragma once

#include "PathSimulatorBase.h"
#include "PresentValueCalculator.h"
#include "PathwiseOperatorGenerator.h"
#include "ExpectationBase.h"
#include "RandomGeneratorBase.h"

#include <boost/shared_ptr.hpp>

class MonteCarloGreeks {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MonteCarloGreeks(
        const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
        const boost::shared_ptr<ExpectationBase>& expectation,
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
    const boost::shared_ptr<ExpectationBase> _expectation;
    const boost::shared_ptr<PathwiseOperatorGenerator> _generator;
    const boost::shared_ptr<RandomGeneratorBase> _randomGenerator;

    /**************************************************************************
     * private functions.
     **************************************************************************/
    inline void initializePath(
        boost::numeric::ublas::matrix<double>& path,
        const boost::numeric::ublas::vector<double>& processes) const;

};



