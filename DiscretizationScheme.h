#pragma once

#include "StochasticDifferentialEquation.h"

#include <boost/shared_ptr.hpp>

class DiscretizationScheme 
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    DiscretizationScheme();
    virtual ~DiscretizationScheme();

    /******************************************************************************
     * pure virtual functions.
     ******************************************************************************/
    virtual void simulateOneStep(
        boost::numeric::ublas::vector<double>& processes, 
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const double time,
        const double timeStepSize,
        std::vector<double>::iterator& random) const = 0;

private:

};

