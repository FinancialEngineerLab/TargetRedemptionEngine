#include "CashFlowCaplet.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
CashFlowCaplet::CashFlowCaplet(
    const double strike,
    const boost::shared_ptr<const Tenor>& tenor)
    :
    _strike(strike),
    _tenor(tenor)
{
}

CashFlowCaplet::~CashFlowCaplet() 
{
}

double CashFlowCaplet::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    const std::size_t maturityIndex = _tenor->getTimeIndex(0);
    const std::size_t assetIndex = _tenor->getAssetIndex(0);
    const double period = _tenor->operator[](1) - _tenor->operator[](0);

    const double cashFlow =  (path(assetIndex, maturityIndex) - _strike);

    return std::max(0.0, period * cashFlow);
}

