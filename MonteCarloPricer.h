#pragma once

#include "PathSimulatorBase.h"
#include "PresentValueCalculator.h"
#include "ExpectationBase.h"

#include <boost/shared_ptr.hpp>

class MonteCarloPricer {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MonteCarloPricer(
        const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
        const boost::shared_ptr<const PresentValueCalculator>& 
            presentValueCalculator,
        const boost::shared_ptr<ExpectationBase>& expectation,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator);
    ~MonteCarloPricer();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    double simulatePrice(
        const boost::numeric::ublas::vector<double>& spots,
        const std::size_t numberOfSimulations,
        const std::vector<double>& observedTimes,
        const boost::numeric::ublas::vector<double>& discountFactors) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const PathSimulatorBase> _pathSimulator;
    const boost::shared_ptr<const PresentValueCalculator> _presentValueCalculator;
    const boost::shared_ptr<ExpectationBase> _expectation;
    const boost::shared_ptr<RandomGeneratorBase> _randomGenerator;

    /**************************************************************************
     * private functions.
     **************************************************************************/
    inline void initializePath(
        boost::numeric::ublas::matrix<double>& path,
        const boost::numeric::ublas::vector<double>& processes) const;

};



