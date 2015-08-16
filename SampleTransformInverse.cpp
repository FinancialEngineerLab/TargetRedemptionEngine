#include "SampleTransformInverse.h"
#include "NewtonRaphson.h"
#include "Solver.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/bind.hpp>

struct Integrand {
    Integrand(Function2DLogInterpolate& function) : _function(function){};
    ~Integrand(){};

    double operator()(
        const double time,
        const double state) {
        return 1.0 / _function(time, state);
    }

    Function2DLogInterpolate _function;
};

/******************************************************************************
 * free functions.
 ******************************************************************************/
inline double linearInterpolate(
    const double v1, 
    const double v2,
    const double y1,
    const double y2,
    const double y)
{
    return (v2 - y) * y1 / (v2 - v1) + (y - v1) * y2 / (v2 - v1);
} 

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
SampleTransformInverse::SampleTransformInverse(
    Function2DLogInterpolate& function2D,
    const double from,
    const double to,
    const std::size_t numberOfPartitions) 
    :
    _function2D(function2D),
    _from(from),
    _to(to),
    _stepSize((to - from) / numberOfPartitions),
    _timeGrid(function2D.getTimeGrid()),
    _map(_timeGrid.size(), numberOfPartitions)
{
    assert(from >= 0.0);
    assert(to >= from);

    const double tolerance = 0.001;
    Solver solver;
    Integrand integrand(_function2D);
    //for all times
    for (std::size_t timeIndex = 0; timeIndex < _timeGrid.size(); ++timeIndex) {
        boost::function<double(double)> function = 
            boost::bind(
                &Function2DLogInterpolate::integrateByState, &_function2D, 
                _timeGrid[timeIndex], _1);
        boost::function<double(double)> differential = 
            boost::bind(
                &Integrand::operator(), &integrand, 
                _timeGrid[timeIndex], _1);

        const boost::shared_ptr<SolverEngine> engine(
            new NewtonRaphson(function, differential));

        //create mapping
        for (std::size_t index = 0; index < numberOfPartitions; ++index) {
            _map(timeIndex, index) = 
                solver.solve(2.0, 
                    from + _stepSize * (index + 1), tolerance, engine);
            //std::cout << _map(timeIndex, index) << "\t\t" << from + _stepSize * (index + 1) << std::endl;
        }
    }

}

SampleTransformInverse::~SampleTransformInverse() 
{
}


double SampleTransformInverse::operator()(
    const double time,
    const double state)
{
    //search timeIndex
    const std::size_t timeIndex = _function2D.searchTimeIndex(time);
    const std::size_t stateIndex = getStateIndex(state);
    
    //inteporate
    const double stepSize = (_to - _from) / _map.size2();
    return linearInterpolate(
        _from + stepSize * stateIndex,
        _from + stepSize * (stateIndex + 1), 
        _map(timeIndex, stateIndex), 
        _map(timeIndex, stateIndex + 1), 
        state);
}


/******************************************************************************
 * private functions.
 ******************************************************************************/
inline std::size_t SampleTransformInverse::getStateIndex(const double state)
{
    return static_cast<std::size_t>((state - _from) / _stepSize);
}

