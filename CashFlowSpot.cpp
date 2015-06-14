#include "CashFlowSpot.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowSpot::CashFlowSpot(
    const std::size_t cashFlowDateIndex,
    const std::size_t maturityIndex, const std::size_t assetIndex)
    :
    _cashFlow(cashFlowDateIndex),
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

std::size_t CashFlowSpot::getCashFlowDateIndex() const
{
    return _cashFlow.getCashFlowDateIndex();
}

