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
    const boost::shared_ptr<const PresentValueCalculator>& presentValueCalculator,
    const boost::shared_ptr<ExpectationBase>& expectation,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator)
    :
    _pathSimulator(pathSimulator),
    _presentValueCalculator(presentValueCalculator),
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
    const boost::numeric::ublas::vector<double>& spots,
    const std::size_t numberOfSimulations,
    const std::vector<double>& observedTimes,
    const boost::numeric::ublas::vector<double>& discountFactors) const
{
    boost::numeric::ublas::vector<double> processes = spots;
    boost::numeric::ublas::matrix<double> 
        path(processes.size(), observedTimes.size(), 0.0);
    initializePath(path, spots);

    std::vector<double> randoms(_randomGenerator->getDimension());

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        ++simulationIndex) {
        //initial settings
        processes = spots;
        boost::numeric::ublas::column(path , 0) = spots;

        //generate randoms
        _randomGenerator->generateNormalRandoms(randoms);

        //simulate path
        _pathSimulator->simulateOnePath(processes, path, observedTimes, randoms);

        //add sample and calculate present value.
        _expectation->addSample(path);
    }
    const double price =_expectation->doExpectation();
    const double variance = _expectation->getVariance();
    std::cout << "variacne:" << variance << std::endl;

    return price;
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

