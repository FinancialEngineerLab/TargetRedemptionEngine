#pragma once

#include "DifferentialDrift.h"
#include "DifferentialDiffusion.h"
#include "StochasticDifferentialEquation.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/multi_array.hpp>


class StochasticDifferentialEquationWithDifferential : 
    public StochasticDifferentialEquation {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    StochasticDifferentialEquationWithDifferential(
        const boost::shared_ptr<const StochasticDifferentialEquation>& 
            stochasticDifferentiaEquation,
        const boost::shared_ptr<const DifferentialDrift> differentialDrfit,
        const boost::shared_ptr<const DifferentialDiffusion> 
            differentialDiffusion);

    virtual ~StochasticDifferentialEquationWithDifferential();

    /**************************************************************************
     * member functions
     **************************************************************************/
    void calculateDifferentialDrift(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& drift) const;
    void calculateDifferentialDiffusion(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::multi_array<double, 3>& diffusion) const;

private:
    /**************************************************************************
     * private variables
     **************************************************************************/
    const boost::shared_ptr<const DifferentialDrift> _differentialDrift;
    const boost::shared_ptr<const DifferentialDiffusion> _differentialDiffusion;
    
};

