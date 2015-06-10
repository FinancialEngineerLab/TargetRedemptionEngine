#include "AntitheticRandom.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
AntitheticRandom::AntitheticRandom(
    boost::shared_ptr<RandomGeneratorBase> innerGenerator_)
    :
    RandomGeneratorBase(innerGenerator_->getDimension()),
    innerGenerator(innerGenerator_),
    isOddNumberOfGenerations(true),
    previousRandoms(innerGenerator_->getDimension()),
    normalDistributionFunction(0.0, 1.0)
{
}

AntitheticRandom::~AntitheticRandom()
{
}

/******************************************************************************
 * inherited pure virtual funcitons.
 ******************************************************************************/
void AntitheticRandom::generateUniformRandoms(std::vector < double > &randoms)
{
    if (isOddNumberOfGenerations) {
        innerGenerator->generateUniformRandoms(randoms);
        std::copy(randoms.begin(), randoms.end(), previousRandoms.begin());
        isOddNumberOfGenerations = false;
    }
    else {
        computeAntithetics(previousRandoms, randoms);
        isOddNumberOfGenerations = true;
    }
}

void AntitheticRandom::generateNormalRandoms(std::vector < double > &randoms)
{
    generateUniformRandoms(randoms);

    for (std::size_t dimensionIndex = 0; 
        dimensionIndex < innerGenerator->getDimension(); dimensionIndex++)
    {
        randoms[dimensionIndex] = 
            inverseNormalCumulativeDistributionFunction
                (randoms[dimensionIndex]);
    }
}

void AntitheticRandom::skip(std::size_t numberOfPath)
{
    innerGenerator->skip(numberOfPath);
}

void AntitheticRandom::setSeed(std::size_t seed)
{
    innerGenerator->setSeed(seed);
}

void AntitheticRandom::reset()
{
    innerGenerator->reset();
}

/******************************************************************************
 * private funcitons.
 ******************************************************************************/
void AntitheticRandom::computeAntithetics(
    std::vector<double> &originVector, std::vector<double> &invertedVector)
{
    for (unsigned int vectorIndex = 0; vectorIndex < originVector.size(); vectorIndex++) {
        invertedVector[vectorIndex] = 1.0 - originVector[vectorIndex];
    }
}

double AntitheticRandom::inverseNormalCumulativeDistributionFunction(
    double probability)
{
    return boost::math::quantile(normalDistributionFunction, probability);
}

