#include "MonteCarloPricerMultiDimensional.h"
#include "utilities.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
MonteCarloPricerMultiDimensional::MonteCarloPricerMultiDimensional(
    const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
    const boost::shared_ptr<ExpectatorsBase>& expectation,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator)
    :
    _pathSimulator(pathSimulator),
    _expectation(expectation),
    _randomGenerator(randomGenerator)
{
}

MonteCarloPricerMultiDimensional::~MonteCarloPricerMultiDimensional() 
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
boost::numeric::ublas::vector<double> 
    MonteCarloPricerMultiDimensional::simulatePrice(
    const boost::numeric::ublas::vector<double>& spot,
    const std::size_t numberOfSimulations,
    const std::vector<double>& observedTimes,
    const boost::numeric::ublas::vector<double>& discountFactors) const
{
    boost::numeric::ublas::vector<double> processes = spot;
    boost::numeric::ublas::matrix<double> 
        path(processes.size(), observedTimes.size(), 0.0);
    initializePath(path, spot);

    std::vector<double> randoms(_randomGenerator->getDimension());

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        ++simulationIndex) {
        //initial settings
        processes = spot;
        boost::numeric::ublas::column(path , 0) = spot;

        //generate randoms
        _randomGenerator->generateNormalRandoms(randoms);

        //simulate path
        _pathSimulator->simulateOnePath(processes, path, observedTimes, randoms);

        //add sample and calculate present value.
        _expectation->addSample(path, observedTimes, randoms);
    }
    boost::numeric::ublas::vector<double> price(spot.size());
    _expectation->doExpectation(price);
    boost::numeric::ublas::vector<double> variance(spot.size());
    _expectation->getVariance(variance);
    std::cout << "variacne:" << variance << std::endl;

    return price;
}


