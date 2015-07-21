#include "ExpectatorsNull.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ExpectatorsNull::ExpectatorsNull()
    :
    //ExpectatorsBase(1UL, boost::shared_ptr<ExpectatorsBase>())
    ExpectatorsBase(1UL)
{
}

ExpectatorsNull::~ExpectatorsNull() 
{
}

void ExpectatorsNull::addSample(
    const boost::numeric::ublas::matrix<double>& path,
    const std::vector<double>& observedTimes,
    const std::vector<double>& randoms)
{
}

void ExpectatorsNull::doExpectation(
    boost::numeric::ublas::vector<double>& result)
{
}

