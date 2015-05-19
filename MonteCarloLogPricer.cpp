#include "MonteCarloLogPricer.h"

#include <cmath>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
MonteCarloLogPricer::MonteCarloLogPricer(
    const boost::shared_ptr<StochasticDifferentialEquation>& model,
    const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator,
    const boost::shared_ptr<PayOff>& payOff)
    :
    MonteCarloPricer(model, discretizationScheme, randomGenerator, payOff)
{
    
}

MonteCarloLogPricer::~MonteCarloLogPricer() 
{
}

/******************************************************************************
 * inherited virtual functions.
 ******************************************************************************/
boost::numeric::ublas::vector<double>& MonteCarloLogPricer::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    const boost::numeric::ublas::vector<double>& spots,
    const double timeStepSize,
    const std::size_t numberOfTimeSteps) const
{
    boost::numeric::ublas::vector<double> logSpots(spots);
    logSpots[0] = log(spots[0]);
    MonteCarloPricer::simulateOnePath(
        processes, logSpots, timeStepSize, numberOfTimeSteps);
    processes[0] = exp(processes[0]);

    return processes;
}
