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

double SampleTransformExp::operator ()(const double time, const double state)
{
    return exp(state);
}

