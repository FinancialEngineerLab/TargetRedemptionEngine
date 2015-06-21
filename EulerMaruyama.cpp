#include "EulerMaruyama.h"
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
EulerMaruyama::EulerMaruyama() 
{
}

EulerMaruyama::~EulerMaruyama() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void EulerMaruyama::simulateOneStep(
    boost::numeric::ublas::vector<double>& processes, 
    const boost::shared_ptr<const StochasticDifferentialEquation>& model,
    const double time,
    const double timeStepSize,
    std::vector<double>::iterator random) const
{
    /**************************************************************************
     * Precomute variables.
     **************************************************************************/
    const std::size_t dimension = model->getDimension();
    const std::size_t dimensionOfBrownianMotion = 
        model->getDimensionOfBrownianMotion();

    boost::numeric::ublas::vector<double> drift(dimension);
    model->calculateDrift(time, processes, drift);
    boost::numeric::ublas::matrix<double> diffusion(
        dimension, dimensionOfBrownianMotion);
    model->calculateDiffusion(time, processes, diffusion);
    boost::numeric::ublas::vector<double> randoms(dimensionOfBrownianMotion);
    generateRandomsVectorFromIterator(randoms, random, dimension);


    //one step calculation.
    processes += timeStepSize * drift 
        + sqrt(timeStepSize) * boost::numeric::ublas::prod(diffusion, randoms);
}


/******************************************************************************
 * private functions.
 ******************************************************************************/
void EulerMaruyama::generateRandomsVectorFromIterator(
    boost::numeric::ublas::vector<double>& randoms,
    std::vector<double>::iterator random,
    const std::size_t dimension) const
{
    for (std::size_t dimensionIndex = 0; dimensionIndex < dimension; 
        ++dimensionIndex) {
        randoms[dimensionIndex] = *random;
        ++random;
    }
}

