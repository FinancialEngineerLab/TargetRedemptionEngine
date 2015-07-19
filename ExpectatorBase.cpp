#include "ExpectatorBase.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ExpectatorBase::ExpectatorBase(const boost::shared_ptr<ExpectatorBase>& next)
    :
    _next(next)
{
    
}
ExpectatorBase::~ExpectatorBase() 
{
}

