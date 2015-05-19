#include "StochasticDifferentialEquationFactory.h"

#include <boost/make_shared.hpp>

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
StochasticDifferentialEquationFactory::StochasticDifferentialEquationFactory() {
}

StochasticDifferentialEquationFactory::~StochasticDifferentialEquationFactory() {
}

/******************************************************************************
 * member functions
 ******************************************************************************/
boost::shared_ptr<StochasticDifferentialEquation> 
    StochasticDifferentialEquationFactory::makeStochasticDifferentialEquation() 
    const
{
    const boost::shared_ptr<Drift> drift = this->makeDrift();
    const boost::shared_ptr<Diffusion> diffusion = this->makeDiffusion();
    const std::size_t dimension = this->makeDimension();
    const std::size_t dimensionOfBrownianMotion = 
        this->makeDimensionOfBrownianMotion();
    const boost::numeric::ublas::matrix<double> correlationMatrix = 
        this->makeCorrelationMatrix();
    
    return boost::make_shared<StochasticDifferentialEquation>(
            drift, diffusion, dimension, dimensionOfBrownianMotion,
            correlationMatrix);
}

