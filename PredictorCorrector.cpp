#include "PredictorCorrector.h"
#include "utilities.h"

#include <boost/numeric/ublas/io.hpp>



/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PredictorCorrector::PredictorCorrector(
    const std::size_t dimensionOfBrownianMotion,
    const double theta,
    const double eta) 
    :
    _eta(eta),
    _theta(theta),
    _drift(1),
    _diffusion(1, dimensionOfBrownianMotion),
    _cacheProcess1(1),
    _cacheProcess2(1)
{
}

PredictorCorrector::~PredictorCorrector() 
{
}


/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void PredictorCorrector::simulateOneStep(
    boost::numeric::ublas::vector<double>& process, 
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const double time,
    const double timeStepSize,
    std::vector<double>::const_iterator& random)
{
    assert(model->getDimension() == 1);
    //Predictor
    _cacheProcess1(0) = exp(process(0));
    model->calculateDrift(time, _cacheProcess1, _drift);
    model->calculateDiffusion(time, _cacheProcess1, _diffusion);
    double diffusionTerm = 0.0;
    for (std::size_t factorIndex = 0; factorIndex < _diffusion.size2(); 
        ++factorIndex) {
        diffusionTerm += _diffusion(0, factorIndex) * (*random);
        random++;
    }
    const double predictor = process(0) + timeStepSize * _drift(0) 
        + sqrt(timeStepSize) * diffusionTerm;
    
    //Corrector
    _cacheProcess2(0) = exp(predictor);
    //calculate drift
    calculateDriftEta(model, time, _cacheProcess1, _drift);
    const double driftEtaPrevious = (1.0 - _theta) * _drift(0);
    calculateDriftEta(model, time + timeStepSize, _cacheProcess2, _drift);
    const double driftEtaNext =  _theta * _drift(0);
    //calculate diffusion
    //TODO: consider multi factor
    model->calculateDiffusion(time, _cacheProcess1, _diffusion);
    const double diffusionPrevious = (1.0 - _eta) * _diffusion(0, 0);
    model->calculateDiffusion(
        time + timeStepSize, _cacheProcess2, _diffusion);
    const double diffusionNext = _eta * _diffusion(0, 0);
    diffusionTerm = 0.0;
    for (std::size_t factorIndex = 0; factorIndex < _diffusion.size2(); 
        ++factorIndex) {
        diffusionTerm += (diffusionPrevious + diffusionNext) * (*random);
        random++;
    }
    
    process(0) += timeStepSize * (driftEtaPrevious + driftEtaNext) 
        + sqrt(timeStepSize) * diffusionTerm;
}


/******************************************************************************
 * member functions.
 ******************************************************************************/
double PredictorCorrector::calculateDriftEta(
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const double time,
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drift)
{
    //TODO: General 
    model->calculateDrift(time, states, drift);
    return drift(0);
}

