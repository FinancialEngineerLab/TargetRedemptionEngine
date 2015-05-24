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
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const = 0;

    //it may be better that the return value is a pointer of the vector class.
    virtual boost::numeric::ublas::vector<double> makeProcesses() const = 0;

private:
            
};

