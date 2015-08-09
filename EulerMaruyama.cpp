#include "EulerMaruyama.h"
#include "utilities.h"

#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
EulerMaruyama::EulerMaruyama(
    const std::size_t dimensionOfBrownianMotion) 
    :
    _drift(1),
    _diffusion(1, dimensionOfBrownianMotion)
{
}

EulerMaruyama::~EulerMaruyama() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
/**
 * @brief only for 1-dim 1-factor process.
 */
void EulerMaruyama::simulateOneStep(
    boost::numeric::ublas::vector<double>& process, 
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const double time,
    const double timeStepSize,
    std::vector<double>::const_iterator& random)
{
    /**************************************************************************
     * Precomute variables.
     **************************************************************************/
    model->calculateDrift(time, process, _drift);
    model->calculateDiffusion(time, process, _diffusion);
    double diffusionTerm = 0.0;
    for (std::size_t factorIndex = 0; factorIndex < _diffusion.size2(); 
        ++factorIndex) {
        diffusionTerm += _diffusion(0, factorIndex) * (*random);
        random++;
    }

    //one step calculation.
    process(0) += timeStepSize * _drift(0) + sqrt(timeStepSize) * diffusionTerm;
}


