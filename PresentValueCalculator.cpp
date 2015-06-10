#include "PresentValueCalculator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PresentValueCalculator::PresentValueCalculator(
    const boost::shared_ptr<const CashFlow>& cashFlow,
    const boost::numeric::ublas::vector<double>& discountFactors)
    :
    _cashFlow(cashFlow),
    _discountFactors(discountFactors)
{
}

PresentValueCalculator::~PresentValueCalculator() 
{
}


double PresentValueCalculator::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    const double cashFlow =  _cashFlow->operator()(path);
    const double discountFactor = 
        _discountFactors[_cashFlow->getCashFlowDateIndex()];
    const double presentValue = cashFlow * discountFactor;

    return presentValue;
}

