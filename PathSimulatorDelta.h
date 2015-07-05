#pragma once

#include "PathSimulatorDecorator.h"

#include <boost/shared_ptr.hpp>

class PathSimulatorDelta : public PathSimulatorDecorator {
public:
    PathSimulatorDelta(
        const boost::shared_ptr<const PathSimulatorBase>& innerSimulator);
    virtual ~PathSimulatorDelta();

    /******************************************************************************
     * inherited virtual functions.
     ******************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        std::vector<double>& randoms) const;

private:
};

