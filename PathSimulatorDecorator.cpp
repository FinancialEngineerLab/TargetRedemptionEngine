#include "PathSimulatorDecorator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PathSimulatorDecorator::PathSimulatorDecorator(
    const boost::shared_ptr<const PathSimulatorBase>& innerSimulator)
    :
    _innerSimulator(innerSimulator)
{
}

PathSimulatorDecorator::~PathSimulatorDecorator() 
{
}

void PathSimulatorDecorator::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    const boost::numeric::ublas::vector<double>& spots,
    const double timeStepSize,
    const std::size_t numberOfTimeSteps) const
{
    return _innerSimulator->simulateOnePath(
        processes, spots, timeStepSize, numberOfTimeSteps);
}

boost::numeric::ublas::vector<double> 
    PathSimulatorDecorator::makeProcesses() const
{
    return _innerSimulator->makeProcesses();
}
