#include "LiborMarketModelDiffusion.h"

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
LiborMarketModelDiffusion::LiborMarketModelDiffusion(
    const boost::numeric::ublas::matrix<double>& volatilities,
    const boost::numeric::ublas::matrix<double>& correlation) 
    :
    _volatilities(volatilities),
    _correlation(correlation)
{
}

LiborMarketModelDiffusion::~LiborMarketModelDiffusion() 
{
}

/******************************************************************************
 * operators.
 ******************************************************************************/
void LiborMarketModelDiffusion::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& diffusions) const
{
    //operation of matrix product: diffusionMatrix * correlationMatrix
    diffusions = boost::numeric::ublas::prod(_volatilities, _correlation);
}

