#pragma once

#include "PathSimulatorDecorator.h"

#include <boost/shared_ptr.hpp>

class BondPathSimulator 
    : public PathSimulatorDecorator
{
public:
    BondPathSimulator(const boost::shared_ptr<const PathSimulatorBase>& innerSimulator);
    virtual ~BondPathSimulator();

    /******************************************************************************
     * inherited virtual functions.
     ******************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const;

private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
            
};

