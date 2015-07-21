#include "PathwiseDeltaCalculator.h"
#include "utilities.h"

#include <vector>
#include <boost/numeric/ublas/matrix_proxy.hpp>

void initializePathwiseOperators(
    std::vector< boost::shared_ptr< boost::numeric::ublas::matrix<double> > > 
        pathwiseOperators,
    const std::size_t rowSize,
    const std::size_t columnSize)
{
    namespace ublas = boost::numeric::ublas;

    pathwiseOperators[0] = boost::shared_ptr< ublas::matrix<double> >(
            new ublas::matrix<double>(rowSize, columnSize, 0.0));

    for (std::size_t vectorIndex = 0; vectorIndex < pathwiseOperators.size(); 
        ++vectorIndex) {
        pathwiseOperators[vectorIndex + 1] = 
            boost::shared_ptr< ublas::matrix<double> >( 
                new ublas::matrix<double>(rowSize, columnSize, 0.0));
    }
}

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
PathwiseDeltaCalculator::PathwiseDeltaCalculator(
    const std::size_t timeLength,
    const std::size_t dimension,
    const boost::shared_ptr<PathwiseOperatorGenerator>& generator,
    const boost::shared_ptr<FunctionMathematics>& payOffFunction)
    :
    _pathwiseOperators(timeLength),
    _generator(generator),
    _payOffFunction(payOffFunction)
{
    initializePathwiseOperators(_pathwiseOperators, dimension, dimension);
}

PathwiseDeltaCalculator::~PathwiseDeltaCalculator() 
{
}


void PathwiseDeltaCalculator::operator()(
    const boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    const std::vector<double>& randoms,
    boost::numeric::ublas::vector<double>& result) const
{
    namespace ublas = boost::numeric::ublas;

    const std::size_t timeLength = _pathwiseOperators.size();

    //calculate differential of the payoff function, 
    //which is initial value of adjoint method.
    ublas::matrix_column< const ublas::matrix<double> > state(path, path.size2());
    _payOffFunction->calculateDifferential(state, result);

    //generate operators in all time.
    std::vector<double>::const_iterator random = randoms.begin();
    for (std::size_t timeIndex = 0; timeIndex < timeLength; ++timeIndex) {
        const double timeStepSize = 
            observedTimes[timeIndex + 1]  - observedTimes[timeIndex];
        const double time = observedTimes[timeIndex];

        //get the state at timeIndex
        ublas::matrix_column< const ublas::matrix<double> > state(path, path.size2());
        //state = ublas::column(path, timeIndex);

        //generate operators.
        _generator->generate(state, 
            *_pathwiseOperators[timeIndex + 1], time, timeStepSize, random);
    }

    //calculate delta by adjoint methods.
    for (std::size_t timeIndex = 0; timeIndex < timeLength; ++timeIndex) {
        result = ublas::prod(result, 
            *_pathwiseOperators[invertIndex(timeIndex, timeLength)]);
    }
}

