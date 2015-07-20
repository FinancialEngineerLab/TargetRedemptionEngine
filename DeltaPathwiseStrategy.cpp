#include "DeltaPathwiseStrategy.h"
#include "FunctionMathematics.h"
#include "Expectation.h"
#include "utilities.h"

void initializePathwiseOperators(
    std::vector< boost::shared_ptr< boost::numeric::ublas::matrix<double> > > 
        pathwiseOperators,
    const std::size_t rowSize,
    const std::size_t columnSize)
{
    namespace ublas = boost::numeric::ublas;

    pathwiseOperators[0] = boost::shared_ptr(
            new identity_matrix<double>(rowSize));

    for (std::size_t vectorIndex = 0; vectorIndex < pathwiseOperators.size(); 
        ++vectorIndex) {
        pathwiseOperators[vectorIndex + 1] = 
            boost::shared_ptr< ublas::vector<double> >( 
                new ublas::matrix<double>(rowSize, columnSize, 0.0));
    }
}

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
    boost::numeric::ublas::vector<double>& spot,
    const std::vector<double> observedTimes,
    const boost::shared_ptr<FunctionMathematics>& payOffFunction,
    const std::size_t numberOfSimulations)
{
    namespace ublas = boost::numeric::ublas;

    const std::size_t timeLength = observedTimes.size();
    boost::shared_ptr<Expectation> 
        expectation(new Expectation(_sampleCalculator));

    ublas::vector<double> processess(0, 0.0);
    ublas::vector<double> stepDelta(spot.size());
    ublas::matrix<double> path(spot.size(), timeLength, 0.0);
    initializePath(path, spot);
    std::vector< ublas::matrix<double> > 
        pathwiseOperators(timeLength);
    initializePathwiseOperators(pathwiseOperators, spot.size(), spot.size());

    std::vector<double> randoms(_randomGenerator->getDimension());

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        simulationIndex++) {
        //generate randoms
        _randomGenerator->generateNormalRandoms(randoms);
           
        //simulate one path
        _pathSimulator->simulateOnePath(spot, path, observedTimes, randoms);

        //calculate differential of the payoff function, 
        //which is initial value of adjoin method.
        state = column(path, path.size2());
        _payOffFunction->calculateDifferential(state, stepDelta);

        //generate operators in all time.
        std::vector<double>::iterator random = randoms.begin();
        for (std::size_t timeIndex = 0; timeIndex < timeLength; ++timeIndex) {
            const double timeStepSize = 
                observedTimes[timeIndex + 1]  - observedTimes[timeIndex];
            const double time = observedTimes[timeIndex];

            //get the state at timeIndex
            const boost::numeric::ublas::matrix_column< boost::numeric::ublas::matrix<double> > 
                state(path, timeIndex);

            //generate operators.
            _generator->generate(state, 
                *pathwiseOperators[timeIndex + 1], time, timeStepSize, random);
        }

        //calculate delta by adjoint methods.
        for (std::size_t timeIndex = 0; timeIndex < timeLength; ++timeIndex) {
            stepDelta = ublas::prod(stepDelta, 
                pathwiseOperators[invertIndex(index, timeLength)]);
        }

        expectation->addSample(path, observedTimes, randoms);
    }

    const double delta = expectation->doExpectation();
    const double variance = expectation->getVariance();

    return delta;
}

