#include "SampleTransformNull.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
SampleTransformNull::SampleTransformNull() 
{
    
}
SampleTransformNull::~SampleTransformNull() 
{
}

double SampleTransformNull::operator ()(const double x) const
{
    return x;
}

void SampleTransformNull::operator ()(
    const boost::numeric::ublas::vector<double>& x,
    boost::numeric::ublas::vector<double>& result) const
{
    for (std::size_t index = 0; index < result.size(); ++index) {
        result[index] = x[index];
    }
} 

