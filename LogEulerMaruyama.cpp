#include "LogEulerMaruyama.h"
#include "utilities.h"

#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
LogEulerMaruyama::LogEulerMaruyama(
    const std::size_t dimensionOfBrownianMotion) 
    :
    _drift(1),
    _diffusion(1, dimensionOfBrownianMotion)
{
}

LogEulerMaruyama::~LogEulerMaruyama() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void LogEulerMaruyama::simulateOneStep(
    boost::numeric::ublas::vector<double>& processes, 
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const double time,
    const double timeStepSize,
    std::vector<double>::const_iterator& random)
{
    assert(model->getDimension() == 1);
    /**************************************************************************
     * Precomute variables.
     **************************************************************************/
    model->calculateDrift(time, processes, _drift);
    model->calculateDiffusion(time, processes, _diffusion);
    double diffusionTerm = 0.0;
    for (std::size_t factorIndex = 0; factorIndex < _diffusion.size2(); 
        ++factorIndex) {
        diffusionTerm += _diffusion(0, factorIndex) * (*random);
        random++;
    }

    //one step calculation.
    processes(0) += timeStepSize * _drift(0) + sqrt(timeStepSize) * diffusionTerm;
}


