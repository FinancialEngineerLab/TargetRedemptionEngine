#include "SabrFactory.h"
#include "SabrDrift.h"
#include "SabrDiffusion.h"

#include <boost/make_shared.hpp>

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
SabrFactory::SabrFactory(const double beta, const double volatility, 
    const boost::numeric::ublas::matrix<double>& correlation)
    :
    _beta(beta),
    _volatility(volatility),
    _dimension(2),
    _dimensionOfBrownianMotion(2),
    _correlation(correlation)
{
}

SabrFactory::~SabrFactory()
{
}

/******************************************************************************
 * inherited pure virtual functions
 ******************************************************************************/
boost::shared_ptr<Drift> SabrFactory::makeDrift() const
{
    return boost::shared_ptr<SabrDrift>(new SabrDrift());
}

boost::shared_ptr<Diffusion> SabrFactory::makeDiffusion() const
{
    return boost::shared_ptr<SabrDiffusion>(
        new SabrDiffusion(_beta, _volatility, _correlation));
}

std::size_t SabrFactory::makeDimension() const
{
    return _dimension;
}
std::size_t SabrFactory::makeDimensionOfBrownianMotion() const
{
    return _dimensionOfBrownianMotion;
}

