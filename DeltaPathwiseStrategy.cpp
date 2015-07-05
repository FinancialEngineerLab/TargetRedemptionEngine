#include "DeltaPathwiseStrategy.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
DeltaPathwiseStrategy::DeltaPathwiseStrategy() 
{
    
}
DeltaPathwiseStrategy::~DeltaPathwiseStrategy() 
{
}


double DeltaPathwiseStrategy::calculate(
    boost::numeric::ublas::vector<double>& delta,
    const boost::numeric::ublas::vector<double> observedTimes)
{
    boost::shared_ptr<Expectation> expectation(new Expectation(sampleCalculator));

    boost::numeric::ublas::vector<double> processess(0, 0.0);
    boost::numeric::ublas::matrix<double> 
        path(processess.size(), observedTimes.size(), 0.0);
    initializePath(path, spots);

    std::vector<double> randoms(_randomGenerator->getDimension());

    for (std::size_t simulationIndex = 0; simulationIndex < _numberOfSimulation;
        simulationIndex++) {
        //generate randoms
        _randomGenerator->generateNormalRandoms(randoms);
           
        //simulate one path
        _pathSimulator->simulateOnePath(processess, path, observedTimes, randoms);

        for (std::size_t timeIndex = 0; timeIndex < observedTimes.size(); ++timeIndex) {
            //generate operator
            _generator->generate(path, pathwiseOperator, timeIndex, randoms);
            stepDelta= pathwiseOperator * stepDelta;
        }

        expectation->addSample(path);
    }

    const double delta = expectation->doExpectation();
    const double variance = expectation->getVariance();

    return delta;
}

