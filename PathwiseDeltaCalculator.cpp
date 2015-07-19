#include "PathwiseDeltaCalculator.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
PathwiseDeltaCalculator::PathwiseDeltaCalculator(const std::size_t dimension)
    :
    _pathwiseOperator(dimension, dimension, 0.0)
{
}

PathwiseDeltaCalculator::~PathwiseDeltaCalculator() 
{
}


double PathwiseDeltaCalculator::operator()(
    const boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    const std::vector<double>& randoms) const
{
    boost::numeric::ublas::vector<double>& stepDelta;
    std::vector<double>::iterator random = randoms.begin();
    for (std::size_t timeIndex = 0; timeIndex < observedTimes.size() - 1; 
        ++timeIndex) {
        const double timeStepSize = observedTimes[timeIndex + 1]  - observedTimes[timeIndex];
        const double time = observedTimes[timeIndex];

        //get the state at timeIndex
        const boost::numeric::ublas::matrix_column< boost::numeric::ublas::matrix<double> > 
            state(path, timeIndex);

        //generate operator
        _generator->generate(state, _pathwiseOperator, time, timeStepSize, random);
        stepDelta = boost::numeric::ublas::prod(_pathwiseOperator, stepDelta);
    }

    return stepDelta;
}

