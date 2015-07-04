#include "PathwiseDeltaCalculator.h"

PathwiseDeltaCalculator::PathwiseDeltaCalculator() 
{
    
}
PathwiseDeltaCalculator::~PathwiseDeltaCalculator() 
{
}

double PathwiseDeltaCalculator::operator()(
    const boost::numeric::ublas::matrix<double>& path)
{
    boost::numeric::ublas::matrix<double> pathwiseOperator(0, 0);
    boost::numeric::ublas::vector<double> stepDelta(0, 0.0);

    for (std::size_t timeIndex = 0; timeIndex < path.size2(); ++timeIndex) {
        _generator->generate(path, pathwiseOperator, timeIndex);

        stepDelta = pathwiseOperator * stepDelta;
    }

    return boost::numeric::ublas::inner_prod(_payOffFunction->differentiate(), stepDelta);
}
