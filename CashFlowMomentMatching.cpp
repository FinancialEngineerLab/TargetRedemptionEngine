#include "CashFlowMomentMatching.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
CashFlowMomentMatching::CashFlowMomentMatching(
    const boost::shared_ptr<CashFlowCalculatorMomentMatching> calculator)
    :
    _calculator(calculator)
{
}

CashFlowMomentMatching::~CashFlowMomentMatching() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double CashFlowMomentMatching::operator()(
    const double sampleAtGrid,
    const std::size_t simulationIndex,
    const std::size_t timeIndex)
{
    return _calculator->operator()(sampleAtGrid, simulationIndex, timeIndex);
}

