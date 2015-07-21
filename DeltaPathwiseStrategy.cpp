#include "DeltaPathwiseStrategy.h"
#include "FunctionMathematics.h"
#include "Expectators.h"
#include "ExpectatorsNull.h"
#include "utilities.h"

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>


/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
DeltaPathwiseStrategy::DeltaPathwiseStrategy(
    const boost::shared_ptr<const SampleCalculator>& sampleCalculator,
    const boost::shared_ptr<const PathSimulator>& pathSimulator,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator,
    const boost::shared_ptr<PathwiseOperatorGenerator>& generator)
    :
    _sampleCalculator(sampleCalculator),
    _pathSimulator(pathSimulator),
    _randomGenerator(randomGenerator),
    _generator(generator)
{
}

DeltaPathwiseStrategy::~DeltaPathwiseStrategy() 
{
}


boost::numeric::ublas::vector<double> DeltaPathwiseStrategy::calculate(
    boost::numeric::ublas::vector<double>& spot,
    const std::vector<double> observedTimes,
    const boost::shared_ptr<FunctionMathematics>& payOffFunction,
    const std::size_t numberOfSimulations)
{
    namespace ublas = boost::numeric::ublas;

    const std::size_t timeLength = observedTimes.size();

    //boost::shared_ptr<ExpectatorsNull> expectatorsNull(
    //    new ExpectatorsNull());
    boost::shared_ptr<Expectators> expectators(
        new Expectators(spot.size(), _sampleCalculator));

    ublas::matrix<double> path(spot.size(), timeLength, 0.0);
    initializePath(path, spot);

    std::vector<double> randoms(_randomGenerator->getDimension());

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        simulationIndex++) {
        //generate randoms
        _randomGenerator->generateNormalRandoms(randoms);
           
        //simulate one path
        _pathSimulator->simulateOnePath(spot, path, observedTimes, randoms);

        expectators->addSample(path, observedTimes, randoms);
    }

    boost::numeric::ublas::vector<double> delta(spot.size());
    expectators->doExpectation(delta);
    boost::numeric::ublas::vector<double> variance(spot.size());
    expectators->getVariance(variance);

    return delta;
}

