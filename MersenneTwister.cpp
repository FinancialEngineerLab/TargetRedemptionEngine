#include "MersenneTwister.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
MersenneTwister::MersenneTwister(
    const std::size_t dimension, 
    const std::size_t seed) 
    :
    RandomGeneratorBase(dimension),
    _mersenneTwister(seed),
    _initialSeed(seed),
    _uniformDistribution(0.0, 1.0),
    _normalDistribution(0.0, 1.0)
{
}

MersenneTwister::~MersenneTwister() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void MersenneTwister::generateUniformRandoms(std::vector<double>& randoms)
{
    generateRandomsWithDistribution(_uniformDistribution, randoms);
}

void MersenneTwister::generateNormalRandoms(std::vector<double>& randoms)
{
    generateRandomsWithDistribution(_normalDistribution, randoms);
}

void MersenneTwister::skip(const std::size_t numberOfPaths)
{
    _mersenneTwister.discard(numberOfPaths * getDimension());
}

void MersenneTwister::setSeed(const std::size_t seed)
{
    _mersenneTwister.seed(seed);
}

void MersenneTwister::reset()
{
    _mersenneTwister.seed(_initialSeed);
}

/******************************************************************************
 * private functions.
 ******************************************************************************/
template <class Distribution>
    void MersenneTwister::generateRandomsWithDistribution(
        Distribution& distribution, std::vector<double>& randoms)
{
    for (std::size_t dimensionIndex = 0; dimensionIndex < getDimension(); 
        ++dimensionIndex) {
        randoms[dimensionIndex] = distribution(_mersenneTwister);
    }
}
