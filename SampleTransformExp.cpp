#include "SampleTransformExp.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
SampleTransformExp::SampleTransformExp() 
{
    
}
SampleTransformExp::~SampleTransformExp() 
{
}

double SampleTransformExp::operator ()(const double x) const
{
    return exp(x);
}

void SampleTransformExp::operator ()(
    const boost::numeric::ublas::vector<double>& x,
    boost::numeric::ublas::vector<double>& result) const
{
    for (std::size_t index = 0; index < result.size(); ++index) {
        result[index] = exp(x[index]);
    }
} 

