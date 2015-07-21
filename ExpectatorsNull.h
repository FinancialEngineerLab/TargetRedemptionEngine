#pragma once

#include "ExpectatorsBase.h"

#include <boost/shared_ptr.hpp>

class ExpectatorsNull : public ExpectatorsBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ExpectatorsNull();
    virtual ~ExpectatorsNull();

    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms);
    virtual void doExpectation(
        boost::numeric::ublas::vector<double>& result);
        
private:
            
};

