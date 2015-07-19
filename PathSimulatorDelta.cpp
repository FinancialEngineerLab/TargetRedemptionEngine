#include "PathSimulatorDelta.h"

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PathSimulatorDelta::PathSimulatorDelta(
    const boost::shared_ptr<const PathSimulatorBase>& innerSimulator)
    :
    PathSimulatorDecorator(innerSimulator)
{
}

PathSimulatorDelta::~PathSimulatorDelta() 
{
}

/******************************************************************************
 * inherited virtual functions.
 ******************************************************************************/
void PathSimulatorDelta::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    std::vector<double>& randoms) const
{
    PathSimulatorDecorator::simulateOnePath(
        processes, path, observedTimes, randoms);
}

