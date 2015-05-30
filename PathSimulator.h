#pragma once

#include "StochasticDifferentialEquation.h"
#include "DiscretizationScheme.h"
#include "RandomGeneratorBase.h"
#include "PathSimulatorBase.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class PathSimulator 
    : public PathSimulatorBase
{
public:
    PathSimulator(
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const boost::shared_ptr<const DiscretizationScheme>& discretizationScheme,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator);
    virtual ~PathSimulator();

    /******************************************************************************
     * virtual functions.
     ******************************************************************************/
    virtual void simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        boost::numeric::ublas::matrix<double>& spotsValues,
        const boost::numeric::ublas::vector<double>& spots,
        const boost::numeric::ublas::vector<double>& observedTimes) const;
    virtual boost::numeric::ublas::vector<double> makeProcesses() const;

private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
    const boost::shared_ptr<const StochasticDifferentialEquation>& _model;
    const boost::shared_ptr<const DiscretizationScheme>& _discretizationScheme;
    const boost::shared_ptr<RandomGeneratorBase>& _randomGenerator;
            
};

