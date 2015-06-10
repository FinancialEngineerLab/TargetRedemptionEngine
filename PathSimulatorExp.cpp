#include "PathSimulatorExp.h"

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

PathSimulatorExp::PathSimulatorExp(
    const boost::shared_ptr<const PathSimulatorBase>& innerSimulator)
    :
    PathSimulatorDecorator(innerSimulator)
{
}

PathSimulatorExp::~PathSimulatorExp() 
{
}

/******************************************************************************
 * inherited virtual functions.
 ******************************************************************************/
void PathSimulatorExp::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes) const
{
    PathSimulatorDecorator::simulateOnePath(
        processes, path, observedTimes);
    expPath(path);
}

void PathSimulatorExp::expPath(
    boost::numeric::ublas::matrix<double>& path) const
{
    for (std::size_t columnIndex = 0; columnIndex < path.size2(); 
        ++columnIndex) {
        for (std::size_t rowIndex = 0; rowIndex < path.size1(); 
            ++rowIndex) {
            path(rowIndex, columnIndex) = exp(path(rowIndex, columnIndex));
        }
    }
}

