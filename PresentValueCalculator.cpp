#include "PresentValueCalculator.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
PresentValueCalculator::PresentValueCalculator(
    const boost::shared_ptr<const CashFlow>& cashFlow,
    const std::vector<double>& discountFactors)
    :
    _cashFlow(cashFlow),
    _discountFactors(discountFactors)
{
}

PresentValueCalculator::~PresentValueCalculator() 
{
}


void PresentValueCalculator::operator()(
    const boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    const std::vector<double>& randoms,
    boost::numeric::ublas::vector<double>& result) const
{
    const double cashFlow =  _cashFlow->operator()(path);
    const double discountFactor = 
        _discountFactors[_cashFlow->getPaymentDateIndex()];
    const double presentValue = cashFlow * discountFactor;

    result[0] = presentValue;
}

