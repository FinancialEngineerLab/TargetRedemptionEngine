#include "FunctionCaplet.h"


/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
FunctionCaplet::FunctionCaplet(const double strike,
    const std::size_t dimensionIndex) 
    :
    _strike(strike),
    _dimensionIndex(dimensionIndex)
{
}

FunctionCaplet::~FunctionCaplet() 
{
}

double FunctionCaplet::operator()(
    const boost::numeric::ublas::vector<double>& spot)
{
    return spot[_dimensionIndex] > _strike ? spot[_dimensionIndex] - _strike : 0.0;
}

void FunctionCaplet::calculateDifferential(
    const boost::numeric::ublas::vector<double>& spot,
    boost::numeric::ublas::vector<double>& result)
{
    for (std::size_t index = 0; index < result.size(); ++index) {
        result[index] = 0.0;
    }
    result[_dimensionIndex] = spot[_dimensionIndex] > _strike ? 1.0 : 0.0;
}

