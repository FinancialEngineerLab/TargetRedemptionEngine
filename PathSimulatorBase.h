#pragma once

#include <boost/numeric/ublas/vector.hpp>

class PathSimulatorBase
{
public:
    PathSimulatorBase();
    virtual ~PathSimulatorBase();

    /**************************************************************************
     * virtual functions.
     **************************************************************************/
    virtual boost::numeric::ublas::vector<double>& simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const = 0;

private:
            
};

