#include "Expectator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
Expectator::Expectator(
    const boost::shared_ptr<const SampleCalculator>& sampleCalculator)
    :
    ExpectatorBase(),
    _sampleCalculator(sampleCalculator),
    _cache(1)
{
}

Expectator::~Expectator() 
{
}

void Expectator::addSample(
    const boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    const std::vector<double>& randoms)
{
    _sampleCalculator->operator()(path, observedTimes, randoms, _cache);
    add(_cache[0]);
}

double Expectator::doExpectation()
{
    return getMean();
}


