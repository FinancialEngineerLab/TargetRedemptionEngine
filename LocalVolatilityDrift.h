#pragma once

#include "Drift.h"
#include "Function1DStepWise.h"
#include "Function2DLogInterpolate.h"

class LocalVolatilityDrift : public Drift {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    LocalVolatilityDrift(
        const Function1DStepWise& drift,
        const Function2DLogInterpolate& interpolatedVolatility);
    virtual ~LocalVolatilityDrift();

    /**************************************************************************
     * inherited  operators.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const;

private:
    const Function1DStepWise _drift;
    const Function2DLogInterpolate _interpolatedVolatility;

};

