#include "BondPathSimulator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
BondPathSimulator::BondPathSimulator(
    const boost::shared_ptr<const PathSimulatorBase>& innerSimulator)
    :
    PathSimulatorDecorator(innerSimulator)
{
}

BondPathSimulator::~BondPathSimulator() 
{
}

/******************************************************************************
 * inherited virtual functions.
 ******************************************************************************/
void BondPathSimulator::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    const boost::numeric::ublas::vector<double>& spots,
    const double timeStepSize,
    const std::size_t numberOfTimeSteps) const
{
    PathSimulatorDecorator::simulateOnePath(
        processes, logSpots, timeStepSize, numberOfTimeSteps);
}

