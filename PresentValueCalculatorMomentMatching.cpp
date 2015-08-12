#include "PresentValueCalculatorMomentMatching.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
PresentValueCalculatorMomentMatching::PresentValueCalculatorMomentMatching(
    const boost::shared_ptr<CashFlowMomentMatching>& cashFlow,
    const std::vector<double>& discountFactors,
    const std::size_t numberOfSimulations)
    :
    _cashFlow(cashFlow),
    _discountFactors(discountFactors)
{
}

PresentValueCalculatorMomentMatching::~PresentValueCalculatorMomentMatching() 
{
}


double PresentValueCalculatorMomentMatching::operator()(
    const double sampleAtGrid,
    const std::size_t simulationIndex,
    const std::size_t timeIndex)
{
    const double cashFlow =  
        _cashFlow->operator()(sampleAtGrid, simulationIndex, timeIndex);
    const double discountFactor = _discountFactors[timeIndex];
    const double presentValue = cashFlow * discountFactor;

    return presentValue;
}

