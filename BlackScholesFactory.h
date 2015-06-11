#pragma once

#include <boost/shared_ptr.hpp>

#include "StochasticDifferentialEquationFactory.h"


class BlackScholesFactory :
    public StochasticDifferentialEquationFactory {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    BlackScholesFactory(const double interestRate, const double dividend, 
        const double volatility);
    virtual ~BlackScholesFactory();

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
    const double _interestRate;
    const double _dividend;
    const double _volatility;
    const std::size_t _dimension;
    const std::size_t _dimensionOfBrownianMotion;
};


class LogBlackScholesFactory :
    public StochasticDifferentialEquationFactory
{
    
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    LogBlackScholesFactory(const double interestRate, const double dividend, 
        const double volatility);
    virtual ~LogBlackScholesFactory();

private:
    /******************************************************************************
     * inherited pure virtual functions.
     ******************************************************************************/
    virtual boost::shared_ptr<Drift> makeDrift() const;
    virtual boost::shared_ptr<Diffusion> makeDiffusion() const;
    virtual std::size_t makeDimension() const;
    virtual std::size_t makeDimensionOfBrownianMotion() const;

    /******************************************************************************
     * private variables.
     ******************************************************************************/
    const double _interestRate;
    const double _dividend;
    const double _volatility;
    const std::size_t _dimension;
    const std::size_t _dimensionOfBrownianMotion;
};

