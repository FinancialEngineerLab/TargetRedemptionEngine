#ifndef MOMENT_MATCHER_H
#define MOMENT_MATCHER_H

#include <iostream>

class MomentMatcher {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    MomentMatcher();
    virtual ~MomentMatcher();

    virtual double doMomentMatch(
        const double sample, 
        const double sampleMean,
        const std::size_t timeIndex) = 0;
    
private:
            
};



#endif

