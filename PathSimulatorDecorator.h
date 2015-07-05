#pragma once

#include "PathSimulatorBase.h"

#include <boost/shared_ptr.hpp>

class PathSimulatorDecorator : public PathSimulatorBase {
public:
    PathSimulatorDecorator(
        const boost::shared_ptr<const PathSimulatorBase>& innerSimulator);
    virtual ~PathSimulatorDecorator();

    /**************************************************************************
     * virtual functions.
     **************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        std::vector<double>& randoms) const;

    /**************************************************************************
     * member functions.
     **************************************************************************/
    boost::numeric::ublas::vector<double> makeProcesses() const;

private:
    const boost::shared_ptr<const PathSimulatorBase> _innerSimulator;
            
};

