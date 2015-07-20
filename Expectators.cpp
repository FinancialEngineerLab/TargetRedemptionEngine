#include "Expectators.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
Expectators::Expectators(
    const boost::shared_ptr<ExpectatorsBase>& next,
    const boost::shared_ptr<const SampleCalculator>& sampleCalculator)
    :
    ExpectatorsBase(next),
    _sampleCalculator(sampleCalculator)
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
    add(_sampleCalculator->operator()(path, observedTimes, randoms));
}

double Expectators::doExpectation()
{
    return getMean();
}

