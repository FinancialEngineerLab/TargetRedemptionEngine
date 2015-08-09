#pragma once

#include "StochasticDifferentialEquation.h"

#include <boost/shared_ptr.hpp>

class DiscretizationScheme {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    DiscretizationScheme();
    virtual ~DiscretizationScheme();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void simulateOneStep(
        boost::numeric::ublas::vector<double>& processes, 
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const double time,
        const double timeStepSize,
        std::vector<double>::const_iterator& iterator)= 0;

private:

};

