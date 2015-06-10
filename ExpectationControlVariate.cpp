#include "ExpectationControlVariate.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ExpectationControlVariate::ExpectationControlVariate(
    const boost::shared_ptr<const PresentValueCalculator>& presentValueCalculator,
    const std::vector< boost::shared_ptr<const PresentValueCalculator> >& 
        controlVariates)
    :
    _presentValueCalculator(presentValueCalculator),
    _controlVariates(controlVariates)
{
}
ExpectationControlVariate::~ExpectationControlVariate()
{
}

void ExpectationControlVariate::addSample(
    const boost::numeric::ublas::matrix<double>& path)
{
    double sumOfControlValue = 0.0;

    for (std::size_t controlIndex = 0; controlIndex < _controlVariates.size(); 
        ++controlIndex) {
        
        sumOfControlValue += _controlVariates[controlIndex]->operator()(path); 
    }

    add(_presentValueCalculator->operator()(path) + sumOfControlValue);
}

double ExpectationControlVariate::doExpectation(
    const std::size_t numberOfSamples)
{
    return getMean();
}

