#pragma once

#include "StochasticDifferentialEquation.h"
#include "DiscretizationScheme.h"
#include "RandomGeneratorBase.h"
#include "PathSimulatorBase.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class PathSimulator : public PathSimulatorBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    PathSimulator(
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const boost::shared_ptr<const DiscretizationScheme>& 
            discretizationScheme);
    virtual ~PathSimulator();

    /**************************************************************************
     * virtual functions.
     **************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        std::vector<double>& randoms) const;
    virtual boost::numeric::ublas::vector<double> makeProcesses() const;

private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const StochasticDifferentialEquation>& _model;
    const boost::shared_ptr<const DiscretizationScheme>& _discretizationScheme;
            
};

