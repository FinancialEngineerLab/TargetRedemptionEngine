#pragma once

#include "MonteCarloPricer.h"

class MonteCarloLogPricer 
    : public MonteCarloPricer
{
public:
    MonteCarloLogPricer(
        const boost::shared_ptr<StochasticDifferentialEquation>& model,
        const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator,
        const boost::shared_ptr<PayOff>& payOff);
    virtual ~MonteCarloLogPricer();

    /**************************************************************************
     * inherited virtual functions.
     **************************************************************************/
    virtual boost::numeric::ublas::vector<double>& simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const;

    private:
};



