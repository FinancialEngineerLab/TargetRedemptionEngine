#include "LiborMarketModelDiffusion.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
LiborMarketModelDiffusion::LiborMarketModelDiffusion(
    const boost::numeric::ublas::matrix<double>& volatilities,
    const boost::numeric::ublas::matrix<double>& correlation,
    const boost::numeric::ublas::vector<double>& tenor) 
    :
    _volatilities(volatilities),
    _correlation(correlation),
    _tenor(tenor)
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

    const std::size_t startIndex = findStartIndex(time);
    const std::size_t rowDimension = diffusions.size1();
    const std::size_t columnDimension = diffusions.size2();

    for (std::size_t dimensionIndex = 0; dimensionIndex < rowDimension; 
        ++dimensionIndex) {
        if (dimensionIndex < startIndex) {
            boost::numeric::ublas::row(diffusions, dimensionIndex) = 
                boost::numeric::ublas::zero_vector<double>(columnDimension);
        }
    }

}

std::size_t LiborMarketModelDiffusion::findStartIndex(const double time) const
{
    for (std::size_t startIndex = 0; startIndex < _tenor.size(); ++startIndex) {
        if (_tenor[startIndex] > time) {
            return startIndex;
        }
    }

    return _tenor.size();
}
