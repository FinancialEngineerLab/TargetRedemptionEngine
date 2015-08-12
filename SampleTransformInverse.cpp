#include "SampleTransformInverse.h"

#include <boost/numeric/ublas/vector.hpp>



/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
SampleTransformInverse::SampleTransformInverse(
    Function2DLogInterpolate& functor,
    const double from,
    const double to
    const std::size_t numberOfPartitions) 
    :
    _functor(functor),
    _from(from),
    _to(to)
{
    assert(from >= 0.0);
    assert(to >= from);
    //create mapping
    for (std::size_t index = 0; index < numberOfPartitions; ++index) {
        
    }
    
}
SampleTransformInverse::~SampleTransformInverse() 
{
}

inline double linearInterpolate(
    const double v1, 
    const double v2,
    const double y1,
    const double y2,
    const double y)
{
    return (v2 - y) * y1 / (v2 - v1) + (y - v1) * y2 / (v2 - v1);
} 

double SampleTransformInverse::operator()(const double x) const
{
    //search the inverse value from map
    
    //linear inteporate
    return 0.0;
}

void SampleTransformInverse::operator()(
    const boost::numeric::ublas::vector<double>& x,
    boost::numeric::ublas::vector<double>& result) const
{

}
