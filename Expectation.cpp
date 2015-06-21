#include "Expectation.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
Expectation::Expectation(
    const boost::shared_ptr<const PresentValueCalculator>& 
        presentValueCalculator)
    :
    _presentValueCalculator(presentValueCalculator)
{
}
Expectation::~Expectation() 
{
}

void Expectation::addSample(const boost::numeric::ublas::matrix<double>& path)
{
    add(_presentValueCalculator->operator()(path));
}

double Expectation::doExpectation()
{
    return getMean();
}
