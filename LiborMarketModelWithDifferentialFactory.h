#pragma once

#include "StochasticDifferentialEquationWithDifferentialFactory.h"
#include "Maturities.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>

class LiborMarketModelWithDifferentialFactory : 
    public StochasticDifferentialEquationWithDifferentialFactory {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    LiborMarketModelWithDifferentialFactory(
        const boost::shared_ptr<const LiborMarketModelFactory>& factory,
        const boost::numeric::ublas::matrix<double>& volatilities,
        const boost::shared_ptr<const Maturities>& maturities,
        const boost::numeric::ublas::matrix<double>& correlation);
    virtual ~LiborMarketModelWithDifferentialFactory();

private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::numeric::ublas::matrix<double> _volatilities;
    const boost::shared_ptr<const Maturities> _maturities;
    const boost::numeric::ublas::matrix<double> _correlation;
    const std::size_t _dimension;

    /**************************************************************************
     * inherited pure virtual funcitons.
     **************************************************************************/
    virtual boost::shared_ptr<Drift> makeDrift() const;
    virtual boost::shared_ptr<Diffusion> makeDiffusion() const;
    virtual std::size_t makeDimension() const;
    virtual std::size_t makeDimensionOfBrownianMotion() const;

    virtual boost::shared_ptr<const DifferentialDrift> 
        makeDifferentialDrift() const;
    virtual boost::shared_ptr<const DifferentialDiffusion> 
        makeDifferentialDiffusion() const;

};

