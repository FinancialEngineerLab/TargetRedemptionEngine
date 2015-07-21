#include "Expectators.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
Expectators::Expectators(
    const std::size_t dimension,
    const boost::shared_ptr<const SampleCalculator>& sampleCalculator)
    :
    ExpectatorsBase(dimension),
    _sampleCalculator(sampleCalculator),
    _cache(dimension)
{
}

Expectators::~Expectators() 
{
}

void Expectators::addSample(
    const boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    const std::vector<double>& randoms)
{
    _sampleCalculator->operator()(path, observedTimes, randoms, _cache);
    add(_cache);
}

void Expectators::doExpectation(
    boost::numeric::ublas::vector<double>& result)
{
    getMean(result);
}


