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
     * inherited pure virtual funcitons.
     **************************************************************************/
    virtual boost::shared_ptr<DifferentialDrift> makeDifferentialDrift() const;
    virtual boost::shared_ptr<DifferentialDiffusion> makeDifferentialDiffusion() const;

    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::numeric::ublas::matrix<double> _volatilities;
    const boost::shared_ptr<const Maturities> _maturities;
    const boost::numeric::ublas::matrix<double> _correlation;
    const std::size_t _dimension;
};

