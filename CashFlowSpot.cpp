#include "CashFlowSpot.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowSpot::CashFlowSpot(
    const std::size_t timeIndex,
    const std::size_t maturityIndex, const std::size_t assetIndex)
    :
    CashFlow(timeIndex),
    _maturityIndex(maturityIndex),
    _assetIndex(assetIndex)
{
}

CashFlowSpot::~CashFlowSpot() 
{
}

double CashFlowSpot::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    return path(_assetIndex, _maturityIndex);
}

