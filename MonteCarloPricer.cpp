#include "MonteCarloPricer.h"
#include "utilities.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
MonteCarloPricer::MonteCarloPricer(
    const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
    const boost::shared_ptr<ExpectatorBase>& expectation,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator)
    :
    _pathSimulator(pathSimulator),
    _expectation(expectation),
    _randomGenerator(randomGenerator)
{
}

MonteCarloPricer::~MonteCarloPricer() 
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
double MonteCarloPricer::simulatePrice(
    const boost::numeric::ublas::vector<double>&  spots,
    const std::size_t numberOfSimulations,
    const std::vector<double>& timeGrid) const
{
    namespace ublas = boost::numeric::ublas;
    ublas::vector<double> processes = spots;
    ublas::matrix<double> path(processes.size(), timeGrid.size(), 0.0);
    initializePath(path, spots);

    std::vector<double> randoms(_randomGenerator->getDimension());

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        ++simulationIndex) {
        //initial settings
        processes = spots;
        ublas::column(path , 0) = spots;

        //generate randoms
        _randomGenerator->generateNormalRandoms(randoms);

        //simulate path
        _pathSimulator->simulateOnePath(processes, path, timeGrid, randoms);

        //add sample and calculate present value.
        _expectation->addSample(path, timeGrid, randoms);
    }
    const double price = _expectation->doExpectation();
    const double variance = _expectation->getVariance();
    std::cout << "variacne:" << variance << std::endl;

    return price;
}


/******************************************************************************
 * private functions.
 ******************************************************************************/

