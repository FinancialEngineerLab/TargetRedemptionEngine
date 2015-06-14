#pragma once

#include "Diffusion.h"
#include "Maturities.h"

class LiborMarketModelDiffusion 
    : public Diffusion {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    LiborMarketModelDiffusion(
        const boost::numeric::ublas::matrix<double>& volatilities,
        const boost::numeric::ublas::matrix<double>& correlation,
        const boost::shared_ptr<const Maturities>& maturities);
    virtual ~LiborMarketModelDiffusion();

    /**************************************************************************
     * inherited  operators.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusions) const;

private:
    /**************************************************************************
     * private variables
     **************************************************************************/
    const boost::numeric::ublas::matrix<double> _volatilities;
    const boost::numeric::ublas::matrix<double> _correlation;
    const boost::shared_ptr<const Maturities> _maturities;

    std::size_t findStartIndex(const double time) const;
};
