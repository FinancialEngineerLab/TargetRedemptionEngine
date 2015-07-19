#include "Expectator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
Expectator::Expectator(
    const boost::shared_ptr<ExpectatorBase>& next,
    const boost::shared_ptr<const SampleCalculator2>& sampleCalculator)
    :
    ExpectatorBase(next),
    _sampleCalculator(sampleCalculator)
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
    add(_sampleCalculator->operator()(path, observedTimes, randoms));
}

double Expectator::doExpectation()
{
    return getMean();
}

