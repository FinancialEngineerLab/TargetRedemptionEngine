#pragma once

#include "ExpectationBase.h"
#include "PresentValueCalculator.h"

#include <boost/shared_ptr.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

class ExpectationControlVariate
    : public ExpectationBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ExpectationControlVariate(
        const boost::shared_ptr<const PresentValueCalculator>& 
            presentValueCalculator,
        const std::vector< boost::shared_ptr<const PresentValueCalculator> >& 
            controlVariates);
    virtual ~ExpectationControlVariate();

    virtual void addSample(const boost::numeric::ublas::matrix<double>& path);
    virtual double doExpectation(const std::size_t numberOfSamples);
        
private:
    const boost::shared_ptr<const PresentValueCalculator> 
        _presentValueCalculator;
    const std::vector< boost::shared_ptr<const PresentValueCalculator> > 
        _controlVariates;

};



