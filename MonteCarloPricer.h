#pragma once

#include "PathSimulatorBase.h"
#include "PathDependent.h"
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
        const boost::shared_ptr<const PathDependent>& pathDependent);
    virtual ~MonteCarloPricer();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    double simulatePrice(
        const boost::numeric::ublas::vector<double>& spots,
        const double maturity,
        const std::size_t numberOfSimulations,
        const boost::numeric::ublas::vector<double>& observedTimes,
        const boost::numeric::ublas::vector<double>& discountFactors) const;
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const PathSimulatorBase> _pathSimulator;
    const boost::shared_ptr<const PathDependent> _pathDependent;

    /**************************************************************************
     * private functions.
     **************************************************************************/
    inline void initializePath(
        boost::numeric::ublas::matrix<double>& path,
        const boost::numeric::ublas::vector<double>& processes) const;

};



