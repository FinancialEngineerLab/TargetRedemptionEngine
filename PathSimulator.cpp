#include "PathSimulator.h"

#include <vector>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
PathSimulator::PathSimulator(
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const boost::shared_ptr<const DiscretizationScheme>& discretizationScheme)
    :
    _model(model),
    _discretizationScheme(discretizationScheme)
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
    const std::vector<double>& observedTimes,
    std::vector<double>& randoms) const
{
    std::vector<double>::const_iterator random = randoms.begin();

    for (std::size_t timeIndex = 0; timeIndex < observedTimes.size() - 1; 
        ++timeIndex) {
        const double timeStepSize = 
            observedTimes[timeIndex + 1] - observedTimes[timeIndex];

        _discretizationScheme->simulateOneStep(
            processes, _model, 
            observedTimes[timeIndex], timeStepSize, random);
        boost::numeric::ublas::column(path, timeIndex + 1) = processes;
    }
}

boost::numeric::ublas::vector<double> PathSimulator::makeProcesses() const
{
    const std::size_t dimension = _model->getDimension();
    boost::numeric::ublas::vector<double> processes(dimension, 0.0);

    return processes;
}


