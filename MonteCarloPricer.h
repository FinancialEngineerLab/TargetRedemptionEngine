#pragma once

#include "PathSimulatorBase.h"
#include "PresentValueCalculator.h"
#include "ExpectatorBase.h"
#include "RandomGeneratorBase.h"
#include "Function2DLogInterpolate.h"

#include <boost/shared_ptr.hpp>

class MonteCarloPricer {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MonteCarloPricer(
        const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
        const boost::shared_ptr<ExpectatorBase>& expectation,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator);
    ~MonteCarloPricer();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    double simulatePrice(
        const boost::numeric::ublas::vector<double>&  spots,
        const std::size_t numberOfSimulations,
        const std::vector<double>& timeGrid,
        const Function2DLogInterpolate& function2D) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const PathSimulatorBase> _pathSimulator;
    const boost::shared_ptr<ExpectatorBase> _expectation;
    const boost::shared_ptr<RandomGeneratorBase> _randomGenerator;

};



