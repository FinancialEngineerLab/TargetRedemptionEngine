#pragma once

#include "Drift.h"
#include "Diffusion.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>


class StochasticDifferentialEquation 
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    StochasticDifferentialEquation(
            const boost::shared_ptr<Drift>& drift, 
            const boost::shared_ptr<Diffusion>& diffusion,
            const std::size_t dimension,
            const std::size_t dimensionOfBrownianMotion);
    virtual ~StochasticDifferentialEquation();

    /**************************************************************************
     * member functions
     **************************************************************************/
    void calculateDrift(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const;
    void calculateDiffusion(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const;
    inline std::size_t getDimension() const;
    inline std::size_t getDimensionOfBrownianMotion() const;

private:
    /**************************************************************************
     * private variables
     **************************************************************************/
    const boost::shared_ptr<Drift> _drift;
    const boost::shared_ptr<Diffusion> _diffusion;
    const std::size_t _dimension;
    const std::size_t _dimensionOfBrownianMotion;
    
};


/******************************************************************************
 * inline functions
 ******************************************************************************/
std::size_t StochasticDifferentialEquation::getDimension() const
{
    return _dimension;
}

std::size_t StochasticDifferentialEquation::getDimensionOfBrownianMotion() const
{
    return _dimensionOfBrownianMotion;
}

