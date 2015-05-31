#include "MonteCarloPricer.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
MonteCarloPricer::MonteCarloPricer(
    const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
    const boost::shared_ptr<const PathDependent>& pathDependent)
    :
    _pathSimulator(pathSimulator),
    _pathDependent(pathDependent)
{
}

MonteCarloPricer::~MonteCarloPricer() 
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
double MonteCarloPricer::simulatePrice(
    const boost::numeric::ublas::vector<double>& spots,
    const std::size_t numberOfSimulations,
    const boost::numeric::ublas::vector<double>& observedTimes,
    const boost::numeric::ublas::vector<double>& discountFactors) const
{
    double sumPrice = 0.0;

    boost::numeric::ublas::vector<double> processes = 
        _pathSimulator->makeProcesses();
    boost::numeric::ublas::matrix<double> 
        path(processes.size(), observedTimes.size(), 0.0);
    initializePath(path, spots);
    boost::numeric::ublas::vector<double> cashFlows(observedTimes.size());

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        ++simulationIndex) {
        _pathSimulator->simulateOnePath(
            processes, path, spots, observedTimes);
        std::cout << path << std::endl;
        _pathDependent->calculateCashFlows(path, cashFlows);
        sumPrice += 
            _pathDependent->calculatePresentValue(cashFlows, discountFactors);
    }

    return sumPrice / numberOfSimulations;
}


/******************************************************************************
 * private functions.
 ******************************************************************************/
inline void MonteCarloPricer::initializePath(
    boost::numeric::ublas::matrix<double>& path,
    const boost::numeric::ublas::vector<double>& processes) const
{
    boost::numeric::ublas::column(path, 0) = processes;
}

