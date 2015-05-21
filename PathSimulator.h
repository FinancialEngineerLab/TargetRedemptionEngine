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
        const boost::shared_ptr<StochasticDifferentialEquation>& model,
        const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator);
    virtual ~PathSimulator();

    /******************************************************************************
     * virtual functions.
     ******************************************************************************/
    virtual boost::numeric::ublas::vector<double>& simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const;

private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
    const boost::shared_ptr<StochasticDifferentialEquation>& _model;
    const boost::shared_ptr<DiscretizationScheme>& _discretizationScheme;
    const boost::shared_ptr<RandomGeneratorBase>& _randomGenerator;
            
};

