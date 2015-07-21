#pragma once

#include "ExpectatorBase.h"
#include "PresentValueCalculator.h"

#include <boost/shared_ptr.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

class ExpectatorControlVariate : public ExpectatorBase {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    ExpectatorControlVariate(
        const boost::shared_ptr<const PresentValueCalculator>& 
            presentValueCalculator,
        const std::vector< boost::shared_ptr<const PresentValueCalculator> >& 
            controlVariates);
    virtual ~ExpectatorControlVariate();

    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms);
    virtual double doExpectation();
        
private:
    const boost::shared_ptr<const PresentValueCalculator> 
        _presentValueCalculator;
    const std::vector< boost::shared_ptr<const PresentValueCalculator> > 
        _controlVariates;
    boost::numeric::ublas::vector<double> _cache;

};


