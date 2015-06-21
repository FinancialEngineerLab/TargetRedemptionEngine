#pragma once

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

class ExpectationBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ExpectationBase();
    virtual ~ExpectationBase();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path) = 0;
    virtual double doExpectation() = 0;

    inline void add(const double sample);
    inline void clear();
    inline double getMean();
    inline double getVariance();
        
private:
    boost::accumulators::accumulator_set<double, 
        boost::accumulators::stats<
            boost::accumulators::tag::mean, 
            boost::accumulators::tag::variance> > _accumulator;
            
};


inline void ExpectationBase::add(const double sample)
{
    _accumulator(sample);
}

inline void ExpectationBase::clear()
{
    _accumulator = 
        boost::accumulators::accumulator_set<double, 
            boost::accumulators::stats<
                boost::accumulators::tag::mean, 
                boost::accumulators::tag::variance> >();
}

inline double ExpectationBase::getMean()
{
    return boost::accumulators::mean(_accumulator);
}

inline double ExpectationBase::getVariance()
{
    return boost::accumulators::variance(_accumulator);
}

