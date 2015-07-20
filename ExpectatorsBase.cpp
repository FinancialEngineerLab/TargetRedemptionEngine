#include "ExpectatorsBase.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ExpectatorsBase::ExpectatorsBase(const boost::shared_ptr<ExpectatorsBase>& next)
    :
    _next(next)
{
    
}
ExpectatorsBase::~ExpectatorsBase() 
{
}

