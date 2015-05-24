#pragma once

#include "PathSimulatorBase.h"
#include "PayOff.h"

#include <boost/shared_ptr.hpp>

class MonteCarloPricer 
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    MonteCarloPricer(
        const boost::shared_ptr<const PathSimulatorBase>& pathSimulator,
        const boost::shared_ptr<const PayOff>& payOff);
    virtual ~MonteCarloPricer();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    double simulatePrice(
        const boost::numeric::ublas::vector<double>& spots,
        const double maturity,
        const std::size_t numberOfSimulations,
        const std::size_t numberOfTimeSteps) const;
    
private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
    const boost::shared_ptr<const PathSimulatorBase> _pathSimulator;
    const boost::shared_ptr<const PayOff>& _payOff;

};



