#include "LiborMarketModelFactory.h"
#include "LiborMarketModelWithDifferentialFactory.h"
#include "DifferentialDrift.h"
#include "DifferentialDiffusion.h"
#include "DifferentialLiborMarketModelDrift.h"
#include "DifferentialLiborMarketModelDiffusion.h"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
LiborMarketModelWithDifferentialFactory::LiborMarketModelWithDifferentialFactory(
    const boost::shared_ptr<const LiborMarketModelFactory>& factory,
    const boost::numeric::ublas::matrix<double>& volatilities,
    const boost::shared_ptr<const Maturities>& maturities,
    const boost::numeric::ublas::matrix<double>& correlation)
    :
    StochasticDifferentialEquationWithDifferentialFactory(factory),
    _volatilities(volatilities),
    _maturities(maturities),
    _correlation(correlation),
    _dimension(volatilities.size1())
{
}

LiborMarketModelWithDifferentialFactory::~LiborMarketModelWithDifferentialFactory()
{
}

/******************************************************************************
 * inherited pure virtual functions
 ******************************************************************************/

boost::shared_ptr<DifferentialDrift> 
    LiborMarketModelWithDifferentialFactory::makeDifferentialDrift() const
{
    return boost::shared_ptr<DifferentialLiborMarketModelDrift>(
        new DifferentialLiborMarketModelDrift(
            _volatilities, _maturities, _dimension));
}

boost::shared_ptr<DifferentialDiffusion> 
    LiborMarketModelWithDifferentialFactory::makeDifferentialDiffusion() const
{
    return boost::shared_ptr<DifferentialLiborMarketModelDiffusion>(
        new DifferentialLiborMarketModelDiffusion());
}

