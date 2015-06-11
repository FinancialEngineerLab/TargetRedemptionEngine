#pragma once

#include "RandomGeneratorBase.h"

#include <boost/random.hpp>

class MersenneTwister 
    : public RandomGeneratorBase {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    MersenneTwister(const std::size_t dimension, const std::size_t seed);
    virtual ~MersenneTwister();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void generateUniformRandoms(std::vector<double>& randoms);
    virtual void generateNormalRandoms(std::vector<double>& randoms);
    virtual void skip(std::size_t numberOfPaths);
    virtual void setSeed(std::size_t seed);
    virtual void reset();
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    boost::mt19937 _mersenneTwister;
    const std::size_t _initialSeed;
    boost::random::uniform_real_distribution<double> _uniformDistribution;
    boost::random::normal_distribution<double> _normalDistribution;

    /**************************************************************************
     * private functions.
     **************************************************************************/
    template <class Distribution>
        void generateRandomsWithDistribution(
            Distribution& distribution, std::vector<double>& randoms);
};

