#include "PathSimulator.h"

#include <vector>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

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
    boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes) const
{
    //generate randoms
    std::vector<double> randoms(_randomGenerator->getDimension());
    _randomGenerator->generateNormalRandoms(randoms);
    std::vector<double>::iterator random = randoms.begin();

    for (std::size_t timeIndex = 1; timeIndex < observedTimes.size(); 
        ++timeIndex) {
        const double timeStepSize = 
            observedTimes[timeIndex] - observedTimes[timeIndex - 1];

        _discretizationScheme->simulateOneStep(
            processes, _model, 
            observedTimes[timeIndex - 1], timeStepSize, random);
        boost::numeric::ublas::column(path, timeIndex) = processes;
    }
}

boost::numeric::ublas::vector<double> PathSimulator::makeProcesses() const
{
    const std::size_t dimension = _model->getDimension();
    boost::numeric::ublas::vector<double> processes(dimension, 0.0);

    return processes;
}


