#pragma once

#include "Drift.h"

#include <boost/numeric/ublas/matrix.hpp>

class LiborMarketModelDrift 
    : public Drift
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    LiborMarketModelDrift(
        const boost::numeric::ublas::matrix<double>& volatilities,
        const boost::numeric::ublas::vector<double>& tenor,
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
    /******************************************************************************
     * private variables.
     ******************************************************************************/
    const boost::numeric::ublas::matrix<double> _volatilities;
    const boost::numeric::ublas::vector<double> _tenor;
    const std::size_t _dimension;

    /******************************************************************************
     * private functions.
     ******************************************************************************/
    std::size_t findStartIndex(const double time) const;
    void calculateSummationInDrift(
        const std::size_t startIndex,
        const std::size_t dimensionIndex,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& rowVector) const;

};
