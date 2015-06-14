#include "LiborMarketModelFactory.h"
#include "LiborMarketModelDrift.h"
#include "LiborMarketModelDiffusion.h"

#include <boost/make_shared.hpp>

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
LiborMarketModelFactory::LiborMarketModelFactory(
    const boost::numeric::ublas::matrix<double>& volatilities,
        const boost::shared_ptr<const Maturities>& maturities,
    const boost::numeric::ublas::matrix<double>& correlation)
    :
    _volatilities(volatilities),
    _maturities(maturities),
    _correlation(correlation),
    _dimension(volatilities.size1()),
    _dimensionOfBrownianMotion(volatilities.size2())
{
}

LiborMarketModelFactory::~LiborMarketModelFactory()
{
}

/******************************************************************************
 * inherited pure virtual functions
 ******************************************************************************/
boost::shared_ptr<Drift> LiborMarketModelFactory::makeDrift() const
{
    return boost::shared_ptr<LiborMarketModelDrift>(
        new LiborMarketModelDrift(_volatilities, _maturities, _dimension));
}

boost::shared_ptr<Diffusion> LiborMarketModelFactory::makeDiffusion() const
{
    return boost::shared_ptr<LiborMarketModelDiffusion>(
        new LiborMarketModelDiffusion(_volatilities, _correlation, _maturities));
}

std::size_t LiborMarketModelFactory::makeDimension() const
{
    return _dimension;
}
std::size_t LiborMarketModelFactory::makeDimensionOfBrownianMotion() const
{
    return _dimensionOfBrownianMotion;
}

