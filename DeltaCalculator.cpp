#include "DeltaCalculator.h"

DeltaCalculator::DeltaCalculator( 
    const boost::shared_ptr<const DeltaStrategy> deltaStrategy)
    :
    _deltaStrategy(deltaStrategy)
{
    
}

DeltaCalculator::~DeltaCalculator() 
{
}

void DeltaCalculator::calculate(
    boost::numeric::ublas::vector<double>& delta)
{
    _deltaStrategy->calculate(delta);
}

