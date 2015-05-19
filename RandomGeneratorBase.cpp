#include "RandomGeneratorBase.h"

RandomGeneratorBase::RandomGeneratorBase(const std::size_t dimension) 
    :
    _dimension(dimension)
{
    
}
RandomGeneratorBase::~RandomGeneratorBase() 
{
}

void RandomGeneratorBase::resetDimension(
    const std::size_t dimension)
{
    _dimension = dimension;
}


