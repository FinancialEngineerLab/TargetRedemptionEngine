#include "CashFlowCaplet.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowCaplet::CashFlowCaplet(
    const std::size_t cashFlowDateIndex,
    const double strike,
    const boost::shared_ptr<const Tenor>& tenor)
    :
    _cashFlow(cashFlowDateIndex),
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
    //std::cout << "maturityIndex:" << maturityIndex << std::endl;
    const std::size_t assetIndex = _tenor->getAssetIndex(0);
    //std::cout << "assetIndex:" << assetIndex << std::endl;
    const double period = _tenor->operator[](1) - _tenor->operator[](0);
    //std::cout << "preod:" << period << std::endl;

    const double discountFactor = 1.0 / (1.0 + period * path(assetIndex, maturityIndex));
    const double cashFlow = discountFactor * (path(assetIndex, maturityIndex) - _strike);
    //std::cout << "cashFlow:" << cashFlow << std::endl;

    return std::max(0.0, period * cashFlow);
}

std::size_t CashFlowCaplet::getCashFlowDateIndex() const
{
    return _cashFlow.getCashFlowDateIndex();
}

