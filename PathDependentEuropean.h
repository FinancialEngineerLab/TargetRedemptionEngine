#pragma once

#include "PathDependent.h"
#include "PayOff.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class PathDependentEuropean 
    : public PathDependent
{
public:
    /******************************************************************************
     * Constructers and Destructers.
     ******************************************************************************/
    PathDependentEuropean(const boost::numeric::ublas::vector<double>& observedTimes,
        const boost::shared_ptr<const PayOff>& payOff);
    virtual ~PathDependentEuropean();

    virtual void calculateCashFlows(
        const boost::numeric::ublas::matrix<double>& spotsValues,
        boost::numeric::ublas::vector<double>& cashFlows) const;

private:
    const boost::shared_ptr<const PayOff>& _payOff;
            
};

