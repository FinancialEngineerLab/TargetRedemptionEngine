#include "PathSimulator.h"



/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PathSimulator::PathSimulator(
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const boost::shared_ptr<const DiscretizationScheme>& discretizationScheme,
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
 * inherited virtual functions.
 ******************************************************************************/
void PathSimulator::simulateOnePath(
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
}

boost::numeric::ublas::vector<double> PathSimulator::makeProcesses() const
{
    const std::size_t dimension = _model->getDimension();
    boost::numeric::ublas::vector<double> processes(dimension, 0.0);

    return processes;
}
