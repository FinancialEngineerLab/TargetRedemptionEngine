#pragma once

#include "DiscretizationScheme.h"
#include "MomentMatcher.h"
#include "PresentValueCalculatorMomentMatching.h"
#include "RandomGeneratorBase.h"

#include <boost/shared_ptr.hpp>

class MonteCarloMomentMatchingPricer {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MonteCarloMomentMatchingPricer(
        const boost::shared_ptr<const StochasticDifferentialEquation>& model, 
        const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
        const boost::shared_ptr<MomentMatcher>& momentMatcher,
        const boost::shared_ptr<PresentValueCalculatorMomentMatching>& 
            presentValueCalculator,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator);
    ~MonteCarloMomentMatchingPricer();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    double simulatePrice(
        const double spots,
        const std::size_t numberOfSimulations,
        const std::vector<double>& timeGrid) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const StochasticDifferentialEquation> _model;
    const boost::shared_ptr<DiscretizationScheme> _discretizationScheme;
    const boost::shared_ptr<MomentMatcher> _momentMatcher;
    const boost::shared_ptr<PresentValueCalculatorMomentMatching> 
        _presentValueCalculator;
    const boost::shared_ptr<RandomGeneratorBase> _randomGenerator;

};



