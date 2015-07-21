#include "LiborMarketModelDrift.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/io.hpp>

/**
 * @brief A constructer of the LiborMarketModelDrift class.
 * @param volatilities
 * @param maturities This variable expresses maturities of forward LIBOR rates. 
 *                   The first index of this variable must be 0. 
 * @param dimension The dimension of LIBOR Market Model processes.
 */
LiborMarketModelDrift::LiborMarketModelDrift(
    const boost::numeric::ublas::matrix<double>& volatilities,
    const boost::shared_ptr<const Maturities>& maturities,
    const std::size_t dimension)
    :
    _volatilities(volatilities),
    _maturities(maturities),
    _dimension(dimension)
{
}

LiborMarketModelDrift::~LiborMarketModelDrift() 
{
}

void LiborMarketModelDrift::operator()(
    const double time, 
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& drifts) const
{
    namespace ublas = boost::numeric::ublas;
    ublas::vector<double> summedRowVector(_dimension, 0.0);

    const std::size_t startIndex = _maturities->findIndexIncludingTime(time);
    for (std::size_t dimensionIndex = 0; dimensionIndex < _dimension; 
        ++dimensionIndex) {
        if (_maturities->operator[](dimensionIndex) > time) {
            summedRowVector.clear();
            calculateSummationInDrift(
                startIndex, dimensionIndex, states, summedRowVector);

            //const boost::numeric::ublas::vector<double>& rowVolatility =
                //boost::numeric::ublas::row(_volatilities, dimensionIndex);
            const ublas::matrix_row< const ublas::matrix<double> > 
                rowVolatility(_volatilities, dimensionIndex);
            drifts[dimensionIndex] = 
                ublas::inner_prod(rowVolatility, summedRowVector);
        } else {
            drifts[dimensionIndex] = 0.0;
        }
    }
}


/******************************************************************************
 * private functions.
 ******************************************************************************/
void LiborMarketModelDrift::calculateSummationInDrift(
    const std::size_t startIndex,
    const std::size_t dimensionIndex,
    const boost::numeric::ublas::vector<double>& states,
    boost::numeric::ublas::vector<double>& rowVector) const
{
    for (std::size_t summationIndex = startIndex; 
        summationIndex < dimensionIndex; ++summationIndex) {
        const boost::numeric::ublas::vector<double>& rowVolatility = 
            boost::numeric::ublas::row(_volatilities, summationIndex);
        const double timeStepSize = 
            (_maturities->operator[](summationIndex + 1) - _maturities->operator[](summationIndex));

        rowVector += rowVolatility * timeStepSize * states[summationIndex]
            / (1.0 + timeStepSize * states[summationIndex]);
    }
}

