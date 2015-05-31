#include "CashFlowSwap.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowSwap::CashFlowSwap(
    const std::size_t maturityIndex,
    const boost::numeric::ublas::vector<double>& tenorIndice,
    const boost::numeric::ublas::vector<double>& periods,
    const double strike)
    :
    _maturityIndex(maturityIndex),
    _swapIndice(swapIndice),
    _tenorIndice(tenorIndice),
    _strike(strike)
{
    
}

CashFlowSwap::~CashFlowSwap() 
{
}

double CashFlowSwap::operator()(
    const boost::numeric::ublas::vector<double>& path) const
{
    double cashFlow = 0.0;
    double discountFactor = 1.0;

    for (std::size_t tenorIndex = 0; tenorIndex < tenorIndice.size(); 
        ++tenorIndex) {
        const std::size_t assetIndex = tenorIndice[tenorIndex];
        discountFactor *= 1.0 / (1.0 
            + _periods[tenorIndex] * path[assetIndex][maturityIndex]);
        cashFlow += _periods[tenorIndex] 
            * (discountFactor * (path[assetIndex][maturityIndex] - _strike);
    }

    return cashFlow;
}

