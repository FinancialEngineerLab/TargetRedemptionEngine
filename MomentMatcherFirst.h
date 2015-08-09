#ifndef MOMENT_MATCHER_FIRST_H
#define MOMENT_MATCHER_FIRST_H

#include "MomentMatcher.h"

#include <boost/numeric/ublas/vector.hpp>

class MomentMatcherFirst : public MomentMatcher {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MomentMatcherFirst(
        const boost::numeric::ublas::vector<double>& expectedValues);
    virtual ~MomentMatcherFirst();

    virtual double doMomentMatch(
        const double sample, 
        const double sampleMean,
        const std::size_t timeIndex);
    
private:
    const boost::numeric::ublas::vector<double> _expectedValues;
};


#endif
