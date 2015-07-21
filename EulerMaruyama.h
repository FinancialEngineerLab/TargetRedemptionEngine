#pragma once

#include "DiscretizationScheme.h"

class EulerMaruyama 
    : public DiscretizationScheme {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    EulerMaruyama();
    virtual ~EulerMaruyama();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void simulateOneStep(
        boost::numeric::ublas::vector<double>& processes, 
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const double time,
        const double timeStepSize,
        std::vector<double>::const_iterator& random) const;

private:
            
};

