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
boost::numeric::ublas::vector<double>& LogPathSimulator::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    const boost::numeric::ublas::vector<double>& spots,
    const double timeStepSize,
    const std::size_t numberOfTimeSteps) const
{
    boost::numeric::ublas::vector<double> logSpots(spots);
    logSpots[0] = log(spots[0]);
    PathSimulatorDecorator::simulateOnePath(
        processes, logSpots, timeStepSize, numberOfTimeSteps);
    processes[0] = exp(processes[0]);

    return processes;
}
