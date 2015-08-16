#include "LogEulerMaruyama.h"
#include "utilities.h"

#include "global.h"

#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
LogEulerMaruyama::LogEulerMaruyama(
    const std::size_t dimensionOfBrownianMotion) 
    :
    _drift(1),
    _diffusion(1, dimensionOfBrownianMotion),
    _cacheProcess(1)
{
}

LogEulerMaruyama::~LogEulerMaruyama() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void LogEulerMaruyama::simulateOneStep(
    boost::numeric::ublas::vector<double>& process, 
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const double time,
    const double timeStepSize,
    std::vector<double>::const_iterator& random)
{
    assert(model->getDimension() == 1);
    /**************************************************************************
     * Precomute variables.
     **************************************************************************/
    _cacheProcess(0) = exp(process(0));
    model->calculateDrift(time, _cacheProcess, _drift);
    model->calculateDiffusion(time, _cacheProcess, _diffusion);
    double diffusionTerm = 0.0;
    for (std::size_t factorIndex = 0; factorIndex < _diffusion.size2(); 
        ++factorIndex) {
        diffusionTerm += _diffusion(0, factorIndex) * (*random);
        random++;
    }

    //one step calculation.
    process(0) += timeStepSize * _drift(0) + sqrt(timeStepSize) * diffusionTerm;
}


