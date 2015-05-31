#pragma once

#include "CashFlowCalculator.h"
#include "PayOff.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class CashFlowEuropean 
    : public CashFlow
{
public:
    /******************************************************************************
     * Constructers and Destructers.
     ******************************************************************************/
    CashFlowEuropean(const boost::numeric::ublas::vector<double>& observedTimes,
        const boost::shared_ptr<const PayOff>& payOff);
    virtual ~CashFlowEuropean();

    virtual void calculateCashFlows(
        const boost::numeric::ublas::matrix<double>& path,
        boost::numeric::ublas::vector<double>& cashFlows) const;

private:
    const boost::shared_ptr<const PayOff>& _payOff;
            
};

