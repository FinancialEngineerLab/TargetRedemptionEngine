#include "PresentValueCalculator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PresentValueCalculator::PresentValueCalculator(
    const boost::shared_ptr<const CashFlow>& cashFlow,
    const boost::numeric::ublas::vector<double>& discountFactors)
    :
    _cashFlow(cashFlow),
    _discoutFactors(discountFactors)
{
}

PresentValueCalculator::~PresentValueCalculator() 
{
}


double PresentValueCalculator::calculatePresentValue(
    const boost::numeric::ublas::matrix<double>& path) const
{
    const double cashFlow =  _cashFlow->operator()(path);
    const double discountFactor = discountFactors[_cashFlow->getTimeIndex()];
    const double presentValue = cashFlow * discountFactor;

    return presetnValue;
}

