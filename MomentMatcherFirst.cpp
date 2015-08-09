#include "MomentMatcherFirst.h"


MomentMatcherFirst::MomentMatcherFirst(
    const boost::numeric::ublas::vector<double>& expectedValues) 
    :
    _expectedValues(expectedValues)
{
}

MomentMatcherFirst::~MomentMatcherFirst() 
{
}


double MomentMatcherFirst::doMomentMatch(
    const double sample,
    const double sampleMean,
    const std::size_t timeIndex)
{
    return sample + _expectedValues(timeIndex) - sampleMean;
}

