#pragma once

#include "Drift.h"
#include "Diffusion.h"

#include "StochasticDifferentialEquation.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>


class StochasticDifferentialEquationWithDifferential : 
    public StochasticDifferentialEquation {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    StochasticDifferentialEquationWithDifferential(
        const StochasticDifferentialEquation& stochasticDifferentiaEquation,
        const boost::shared_ptr<const DriftDifferential> differentialDrfit,
        const boost::shared_ptr<const DiffusionDifferential> differentialDiffusion);

    virtual ~StochasticDifferentialEquationWithDifferential();

    /**************************************************************************
     * member functions
     **************************************************************************/
    virtual void calculateDrift(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const;
    virtual void calculateDiffusion(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const;
    void calculateDifferentialDrift(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const;
    void calculateDifferentialDiffusion(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const;

private:
    /**************************************************************************
     * private variables
     **************************************************************************/
    const boost::shared_ptr<const DifferentialDrift> _drift;
    const boost::shared_ptr<const DifferentialDiffusion> _diffusion;
    
};

