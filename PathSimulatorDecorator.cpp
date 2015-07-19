#include "PathSimulatorDecorator.h"

/******************************************************************************
 * Constructers and Destructer.
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
    const std::vector<double>& observedTimes,
    std::vector<double>& randoms) const
{
    _innerSimulator->simulateOnePath(processes, path, observedTimes, randoms);
}

boost::numeric::ublas::vector<double> 
    PathSimulatorDecorator::makeProcesses() const
{
    return _innerSimulator->makeProcesses();
}
