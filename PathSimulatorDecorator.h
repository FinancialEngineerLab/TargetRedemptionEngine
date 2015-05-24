#pragma once

#include "PathSimulatorBase.h"

#include <boost/shared_ptr.hpp>

class PathSimulatorDecorator
    : public PathSimulatorBase
{
public:
    PathSimulatorDecorator(const boost::shared_ptr<const PathSimulatorBase>& innerSimulator);
    virtual ~PathSimulatorDecorator();

    /**************************************************************************
     * virtual functions.
     **************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const;


    /**************************************************************************
     * member functions.
     **************************************************************************/
    boost::numeric::ublas::vector<double> makeProcesses() const;

private:
    const boost::shared_ptr<const PathSimulatorBase> _innerSimulator;
            
};

