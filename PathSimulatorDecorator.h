#pragma once

#include "PathSimulatorBase.h"

#include <boost/shared_ptr.hpp>

class PathSimulatorDecorator
    : public PathSimulatorBase
{
public:
    PathSimulatorDecorator(const boost::shared_ptr<const PathSimulatorBase>& innerSimulator);
    virtual ~PathSimulatorDecorator();

    /******************************************************************************
     * virtual functions.
     ******************************************************************************/
    virtual boost::numeric::ublas::vector<double>& simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const;

private:
    const boost::shared_ptr<const PathSimulatorBase> _innerSimulator;
            
};

