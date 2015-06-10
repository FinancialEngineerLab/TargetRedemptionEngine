#include "CashFlowSwap.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CashFlowSwap::CashFlowSwap(
    const std::vector<double>& observedTimes,
    const std::vector<std::size_t>& tenorToTime,
    const std::vector<std::size_t>& tenorToAsset,
    const double strike)
    :
    CashFlow(tenorToTime[0]),
    _observedTimes(observedTimes),
    _tenorToTime(tenorToTime),
    _tenorToAsset(tenorToAsset),
    _strike(strike)
{
}

CashFlowSwap::~CashFlowSwap() 
{
}

double CashFlowSwap::operator()(
    const boost::numeric::ublas::matrix<double>& path) const
{
    double cashFlow = 0.0;
    double discountFactor = 1.0;
    const std::size_t maturityIndex = _tenorToTime[0];

    for (std::size_t tenorIndex = 0; tenorIndex < _tenorToTime.size() - 1; 
        ++tenorIndex) {
        const std::size_t assetIndex = _tenorToAsset[tenorIndex];
        const std::size_t timeIndex0 = _tenorToTime[tenorIndex];
        const std::size_t timeIndex1 = _tenorToTime[tenorIndex + 1];
        const double period = 
            _observedTimes[timeIndex1] - _observedTimes[timeIndex0];

        discountFactor *= 1.0 / (1.0 + period * path(assetIndex, maturityIndex));
        cashFlow += period 
            * discountFactor * (path(assetIndex, maturityIndex) - _strike);
    }

    return cashFlow;
}

