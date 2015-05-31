#include "PayOffCaplet.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
PayOffCaplet::PayOffCaplet(const double strike, const std::size_t maturityIndex,
    const boost::numeric::ublas::vector<double>& tenor,
    const boost::numeric::ublas::vector<double>& discountFactors) 
    :
    _strike(strike),
    _maturityIndex(maturityIndex),
    _tenor(tenor)
{
    _tenor[strike]
    for (std::size_t tenorIndex = 0; tenorIndex < maturityIndex; ++tenorIndex) {
        discountFactor *= 1.0 / (1.0 + maturi
    }
}

PayOffCaplet::~PayOffCaplet() 
{
}

double PayOffCaplet::payOffFunction(
    const boost::numeric::ublas::vector<double>& spots) const
{
    const double timeDifference = 
        _tenor[_maturityIndex + 1] - _tenor[_maturityIndex];


    return timeDifference * std::max(0.0, spots[_maturityIndex] - _strike);
}

