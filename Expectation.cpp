#include "Expectation.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
Expectation::Expectation(
    const boost::shared_ptr<const SampleCalculator>& sampleCalculator)
    :
    _sampleCalculator(sampleCalculator)
{
}
Expectation::~Expectation() 
{
}

void Expectation::addSample(const boost::numeric::ublas::matrix<double>& path)
{
    add(_sampleCalculator->operator()(path));
}

double Expectation::doExpectation()
{
    return getMean();
}
