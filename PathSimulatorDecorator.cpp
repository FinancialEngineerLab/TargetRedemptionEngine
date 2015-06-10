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
    boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes) const
{
    return _innerSimulator->simulateOnePath(
        processes, path, observedTimes);
}

boost::numeric::ublas::vector<double> 
    PathSimulatorDecorator::makeProcesses() const
{
    return _innerSimulator->makeProcesses();
}
