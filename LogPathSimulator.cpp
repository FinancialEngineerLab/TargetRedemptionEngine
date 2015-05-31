#include "LogPathSimulator.h"

LogPathSimulator::LogPathSimulator(
    const boost::shared_ptr<const PathSimulatorBase>& innerSimulator)
    :
    PathSimulatorDecorator(innerSimulator)
{
}

LogPathSimulator::~LogPathSimulator() 
{
}

/******************************************************************************
 * inherited virtual functions.
 ******************************************************************************/
void LogPathSimulator::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    boost::numeric::ublas::matrix<double>& spotsValues,
    const boost::numeric::ublas::vector<double>& spots,
    const std::vector<double>& observedTimes) const
{
    boost::numeric::ublas::vector<double> logSpots(spots);
    logSpots[0] = log(spots[0]);
    PathSimulatorDecorator::simulateOnePath(
        processes, spotsValues, logSpots, observedTimes);
    processes[0] = exp(processes[0]);
}

