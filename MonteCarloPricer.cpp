#include "MonteCarloPricer.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
MonteCarloPricer::MonteCarloPricer(
    const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
    const boost::shared_ptr<const PayOff>& payOff)
    :
    _pathSimulator(pathSimulator),
    _payOff(payOff)
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
    const double maturity,
    const std::size_t numberOfSimulations,
    const std::size_t numberOfTimeSteps) const
{
    double sumPrice = 0.0;
    const double timeStepSize = maturity / numberOfTimeSteps;

    boost::numeric::ublas::vector<double> processes = _pathSimulator->makeProcesses();

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        ++simulationIndex) {
        _pathSimulator->simulateOnePath(
            processes, spots, timeStepSize, numberOfTimeSteps);
        sumPrice += _payOff->payOffFunction(processes);
    }

    return sumPrice / numberOfSimulations;
}

