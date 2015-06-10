#pragma once

#include "RandomGeneratorBase.h"

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/math/distributions.hpp>

class AntitheticRandom :
    public RandomGeneratorBase
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    AntitheticRandom(boost::shared_ptr<RandomGeneratorBase> innerGenerator_);
    virtual ~AntitheticRandom();

    /**************************************************************************
     * inherited pure virtual funcitons.
     **************************************************************************/
    virtual void generateUniformRandoms(std::vector<double> &randoms);
    virtual void generateNormalRandoms(std::vector<double> &randoms);
    virtual void skip(unsigned long numberOfPaths);
    virtual void setSeed(unsigned long seed);
    virtual void reset();

private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    boost::shared_ptr<RandomGeneratorBase> innerGenerator;
    bool isOddNumberOfGenerations;
    std::vector<double> previousRandoms;
    boost::math::normal_distribution<> normalDistributionFunction;

    /**************************************************************************
     * private funcitons.
     **************************************************************************/
    void computeAntithetics(
        std::vector<double> &originVector, std::vector<double> &invertedVector);
    double inverseNormalCumulativeDistributionFunction(double probability);
};

