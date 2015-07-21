#include "MonteCarloGreeks.h"
#include "utilities.h"

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
MonteCarloGreeks::MonteCarloGreeks(
    const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
    const boost::shared_ptr<ExpectatorBase>& expectation,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator)
    :
    _pathSimulator(pathSimulator),
    _expectation(expectation),
    _randomGenerator(randomGenerator)
{
}

MonteCarloGreeks::~MonteCarloGreeks() 
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
double MonteCarloGreeks::simulate(
    const boost::numeric::ublas::vector<double>& spots,
    const std::size_t numberOfSimulations,
    const std::vector<double>& observedTimes,
    const boost::numeric::ublas::vector<double>& discountFactors) const
{
    boost::numeric::ublas::vector<double> processes = spots;
    boost::numeric::ublas::matrix<double> 
        path(processes.size(), observedTimes.size(), 0.0);
    initializePath(path, spots);
    boost::numeric::ublas::matrix<double> 
        pathwiseOperator(spots.size(), spots.size(), 0.0);

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

        std::vector<double>::iterator random = randoms.begin();
        boost::numeric::ublas::vector<double> stepDelta(spots.size(), 0.0);
        for (std::size_t timeIndex = 0; timeIndex < observedTimes.size(); 
            ++timeIndex) {
            //get brownian motion
            const double timeStepSize = 0.0;
            const double time = observedTimes[timeIndex];

            //get the state at timeIndex
            const boost::numeric::ublas::matrix_column< boost::numeric::ublas::matrix<double> > 
                state(path, timeIndex);

            //generate operator
            _generator->generate(state, pathwiseOperator, time, timeStepSize, random);
            stepDelta = boost::numeric::ublas::prod(pathwiseOperator, stepDelta);
        }

        //add sample and calculate present value.
        _expectation->addSample(path, observedTimes, randoms);
    }
    const double greeks =_expectation->doExpectation();
    const double variance = _expectation->getVariance();
    std::cout << "variacne:" << variance << std::endl;

    return greeks;
}


/******************************************************************************
 * private functions.
 ******************************************************************************/
inline void MonteCarloGreeks::initializePath(
    boost::numeric::ublas::matrix<double>& path,
    const boost::numeric::ublas::vector<double>& processes) const
{
    boost::numeric::ublas::column(path, 0) = processes;
}

