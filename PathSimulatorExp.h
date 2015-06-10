#pragma once

#include "PathSimulatorDecorator.h"

#include <boost/shared_ptr.hpp>

class PathSimulatorExp 
    : public PathSimulatorDecorator
{
public:
    PathSimulatorExp(const boost::shared_ptr<const PathSimulatorBase>& innerSimulator);
    virtual ~PathSimulatorExp();

    /******************************************************************************
     * inherited virtual functions.
     ******************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes) const;

private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
    void expPath(boost::numeric::ublas::matrix<double>& path) const;
};

