#include "PathSimulator.h"


/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PathSimulator::PathSimulator(
    const boost::shared_ptr<StochasticDifferentialEquation>& model,
    const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator)
    :
    _model(model),
    _discretizationScheme(discretizationScheme),
    _randomGenerator(randomGenerator)
{
}

PathSimulator::~PathSimulator() 
{
}


/******************************************************************************
 * virtual functions.
 ******************************************************************************/
boost::numeric::ublas::vector<double>& PathSimulator::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    const boost::numeric::ublas::vector<double>& spots,
    const double timeStepSize,
    const std::size_t numberOfTimeSteps) const
{
    double time = 0.0;
    processes = spots;
    std::vector<double> randoms(_randomGenerator->getDimension());
    _randomGenerator->generateNormalRandoms(randoms);
    std::vector<double>::iterator random = randoms.begin();

    for (std::size_t timeIndex = 0; timeIndex <  numberOfTimeSteps; 
        ++timeIndex) {
        _discretizationScheme->simulateOneStep(
            processes, _model, time, timeStepSize, random);

        time += timeStepSize;
    }

    return processes;
}


