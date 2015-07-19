#include "DeltaPathwiseStrategy.h"
#include "Expectation.h"
#include "utilities.h"

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


double DeltaPathwiseStrategy::calculate(
    boost::numeric::ublas::vector<double>& stepDelta,
    const std::vector<double> observedTimes,
    const std::size_t numberOfSimulations)
{
    boost::shared_ptr<Expectation> 
        expectation(new Expectation(_sampleCalculator));

    boost::numeric::ublas::vector<double> processess(0, 0.0);
    boost::numeric::ublas::matrix<double> 
        path(processess.size(), observedTimes.size(), 0.0);
    initializePath(path, stepDelta);
    boost::numeric::ublas::matrix<double> 
        pathwiseOperator(stepDelta.size(), stepDelta.size(), 0.0);

    std::vector<double> randoms(_randomGenerator->getDimension());


    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        simulationIndex++) {
        boost::numeric::ublas::vector<double> stepDelta(stepDelta.size(), 0.0);
        //generate randoms
        _randomGenerator->generateNormalRandoms(randoms);
           
        //simulate one path
        _pathSimulator->simulateOnePath(
            stepDelta, path, observedTimes, randoms);

        std::vector<double>::iterator random = randoms.begin();
        for (std::size_t timeIndex = 0; timeIndex < observedTimes.size() - 1; 
            ++timeIndex) {
            const double timeStepSize = observedTimes[timeIndex + 1]  - observedTimes[timeIndex];
            const double time = observedTimes[timeIndex];

            //get the state at timeIndex
            const boost::numeric::ublas::matrix_column< boost::numeric::ublas::matrix<double> > 
                state(path, timeIndex);

            //generate operator
            _generator->generate(state, pathwiseOperator, time, timeStepSize, random);
            stepDelta = boost::numeric::ublas::prod(pathwiseOperator, stepDelta);
        }

        expectation->addSample(path);
    }

    const double delta = expectation->doExpectation();
    const double variance = expectation->getVariance();

    return delta;
}


