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

double SampleTransformNull::operator ()(
    const double time,
    const double state)
{
    return state;
}


