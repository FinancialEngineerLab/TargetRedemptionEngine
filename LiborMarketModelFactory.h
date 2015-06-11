#pragma once

#include <boost/shared_ptr.hpp>

#include "StochasticDifferentialEquationFactory.h"


class LiborMarketModelFactory :
    public StochasticDifferentialEquationFactory {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    LiborMarketModelFactory(
        const boost::numeric::ublas::matrix<double>& volatilities,
        const boost::numeric::ublas::vector<double>& maturities,
        const boost::numeric::ublas::matrix<double>& correlation);
    virtual ~LiborMarketModelFactory();

private:
    /**************************************************************************
     * inherited pure virtual funcitons.
     **************************************************************************/
    virtual boost::shared_ptr<Drift> makeDrift() const;
    virtual boost::shared_ptr<Diffusion> makeDiffusion() const;
    virtual std::size_t makeDimension() const;
    virtual std::size_t makeDimensionOfBrownianMotion() const;

    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::numeric::ublas::matrix<double> _volatilities;
    const boost::numeric::ublas::vector<double> _maturities;
    const boost::numeric::ublas::matrix<double> _correlation;
    const std::size_t _dimension;
    const std::size_t _dimensionOfBrownianMotion;
};

