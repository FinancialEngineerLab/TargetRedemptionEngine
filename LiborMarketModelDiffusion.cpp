#include "LiborMarketModelDiffusion.h"
#include "Maturities.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/shared_ptr.hpp>

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
LiborMarketModelDiffusion::LiborMarketModelDiffusion(
    const boost::numeric::ublas::matrix<double>& volatilities,
    const boost::numeric::ublas::matrix<double>& correlation,
    const boost::shared_ptr<const Maturities>& maturities)
    :
    _volatilities(volatilities),
    _correlation(correlation),
    _maturities(maturities)
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

    const std::size_t rowDimension = diffusions.size1();
    const std::size_t columnDimension = diffusions.size2();

    for (std::size_t dimensionIndex = 0; dimensionIndex < rowDimension; 
        ++dimensionIndex) {
        if (_maturities->operator[](dimensionIndex) < time) {
            boost::numeric::ublas::row(diffusions, dimensionIndex) = 
                boost::numeric::ublas::zero_vector<double>(columnDimension);
        } else {
            boost::numeric::ublas::row(diffusions, dimensionIndex) 
                *=  states[dimensionIndex];
        }
    }

}


