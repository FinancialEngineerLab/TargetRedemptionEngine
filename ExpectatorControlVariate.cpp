#include "ExpectatorControlVariate.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
ExpectatorControlVariate::ExpectatorControlVariate(
    const boost::shared_ptr<const PresentValueCalculator>& presentValueCalculator,
    const std::vector< boost::shared_ptr<const PresentValueCalculator> >& 
        controlVariates)
    :
    _presentValueCalculator(presentValueCalculator),
    _controlVariates(controlVariates),
    _cache(1)
{
}
ExpectatorControlVariate::~ExpectatorControlVariate()
{
}

void ExpectatorControlVariate::addSample(
    const boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    const std::vector<double>& randoms)
{
    double sumOfControlValue = 0.0;

    for (std::size_t controlIndex = 0; controlIndex < _controlVariates.size(); 
        ++controlIndex) {
        _controlVariates[controlIndex]->operator()(path, observedTimes, randoms, _cache); 
        sumOfControlValue += _cache[0];
    }
    _presentValueCalculator->operator()(path, observedTimes, randoms, _cache);
    add(_cache[0] + sumOfControlValue);
}

double ExpectatorControlVariate::doExpectation()
{
    return getMean();
}


