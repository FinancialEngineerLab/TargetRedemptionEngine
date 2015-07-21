#pragma once

#include "PathSimulatorBase.h"
#include "ExpectatorsBase.h"
#include "RandomGeneratorBase.h"

#include <boost/shared_ptr.hpp>

class MonteCarloPricerMultiDimensional {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MonteCarloPricerMultiDimensional(
        const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
        const boost::shared_ptr<ExpectatorsBase>& expectation,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator);
    ~MonteCarloPricerMultiDimensional();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    boost::numeric::ublas::vector<double> simulatePrice(
        const boost::numeric::ublas::vector<double>& spot,
        const std::size_t numberOfSimulations,
        const std::vector<double>& observedTimes,
        const boost::numeric::ublas::vector<double>& discountFactors) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const PathSimulatorBase> _pathSimulator;
    const boost::shared_ptr<ExpectatorsBase> _expectation;
    const boost::shared_ptr<RandomGeneratorBase> _randomGenerator;

};



