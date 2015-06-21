#include "CashFlowPut.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
CashFlowPut::CashFlowPut(
    const double strike,
    const std::size_t assetIndex,
    const std::size_t maturityIndex)
    :
    _strike(strike),
    _assetIndex(assetIndex),
    _maturityIndex(maturityIndex)
{
}

CashFlowPut::~CashFlowPut() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double CashFlowPut::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    assert(0 <= _assetIndex);
    assert(_assetIndex < path.size1());
    assert(0 <= _maturityIndex);
    assert(_maturityIndex < path.size2());

    const double cashFlow = path(_assetIndex, _maturityIndex);

    return std::max(0.0, _strike - cashFlow);
}

