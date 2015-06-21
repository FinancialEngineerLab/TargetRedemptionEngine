#pragma once

#include "Drift.h"
#include "Maturities.h"

#include <boost/numeric/ublas/matrix.hpp>

class LiborMarketModelDrift 
    : public Drift {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    LiborMarketModelDrift(
        const boost::numeric::ublas::matrix<double>& volatilities,
        const boost::shared_ptr<const Maturities>& maturities,
        const std::size_t dimension);
    virtual ~LiborMarketModelDrift();

    /**************************************************************************
     * inherited  operators.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drifts) const;

private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::numeric::ublas::matrix<double> _volatilities;
    const boost::shared_ptr<const Maturities>& _maturities;
    const std::size_t _dimension;

    /**************************************************************************
     * private functions.
     **************************************************************************/
    void calculateSummationInDrift(
        const std::size_t startIndex,
        const std::size_t dimensionIndex,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& rowVector) const;

};
