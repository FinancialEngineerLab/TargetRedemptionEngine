#pragma once

#include "PathSimulatorDecorator.h"

#include <boost/shared_ptr.hpp>

class LogPathSimulator 
    : public PathSimulatorDecorator
{
public:
    LogPathSimulator(const boost::shared_ptr<const PathSimulatorBase>& innerSimulator);
    virtual ~LogPathSimulator();

    /******************************************************************************
     * inherited virtual functions.
     ******************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        boost::numeric::ublas::matrix<double>& spotsValues,
        const boost::numeric::ublas::vector<double>& spots,
        const std::vector<double>& observedTimes) const;
    //boost::numeric::ublas::vector<double> makeProcesses() const;

private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
            
};

