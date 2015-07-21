#include "DifferentialLiborMarketModelDrift.h"
#include "utilities.h"

#include <boost/numeric/ublas/vector.hpp>
#include <iostream>

/**************************************************************************
 * Constructers and Destructer.
 **************************************************************************/
DifferentialLiborMarketModelDrift::DifferentialLiborMarketModelDrift(
    const boost::numeric::ublas::matrix<double>& volatilities,
    const boost::shared_ptr<const Maturities>& maturities,
    const std::size_t dimension)
    :
    _volatilities(volatilities),
    _maturities(maturities),
    _dimension(dimension)
{
}
DifferentialLiborMarketModelDrift::~DifferentialLiborMarketModelDrift() 
{
}

void DifferentialLiborMarketModelDrift::calculate(
    const double time,
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& result) const
{
    for (std::size_t rowIndex1 = 0; rowIndex1 < result.size1(); ++rowIndex1) {
        if (isBeforeMaturity(time, rowIndex1)) {
            calculateDifferentialElement(time, states, result, rowIndex1);
        }
    }
}

bool DifferentialLiborMarketModelDrift::isBeforeMaturity(
    const double time,
    const std::size_t liborIndex) const
{
    return (_maturities->operator[](liborIndex) > time);
}

/**
 * @brief calculate the elements of differential of drift, which is calculated by
 *        sigma_{i}^{T} sigma_{k} delta_{k} 
 *        / (1 + delta_{k}L_{k}(n))^{2}. Here i is rowIndex1, k is rowIndex2.
 */
void DifferentialLiborMarketModelDrift::calculateDifferentialElement(
    const double time,
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::matrix<double>& result,
    const std::size_t rowIndex1) const
{
    namespace ublas = boost::numeric::ublas;

    ublas::matrix_row< const ublas::matrix<double> > 
        rowVolatility1(_volatilities, rowIndex1);

    for (std::size_t rowIndex2 = 0; rowIndex2 < result.size1(); ++rowIndex2) {
        const double timeStepSize = 
            (_maturities->operator[](rowIndex2 + 1) 
                 - _maturities->operator[](rowIndex2));
        ublas::matrix_row< const ublas::matrix<double> > 
            rowVolatility2(_volatilities, rowIndex2);
        const double innerProduct = 
            ublas::inner_prod(rowVolatility1, rowVolatility2);

        result(rowIndex1, rowIndex2) = innerProduct * timeStepSize 
            / square(1.0 + timeStepSize * states[rowIndex2]);
    }
}

