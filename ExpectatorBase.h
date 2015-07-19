#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>


class ExpectatorBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ExpectatorBase(
        const boost::shared_ptr<ExpectatorBase>& next);
    virtual ~ExpectatorBase();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms) = 0;
    virtual double doExpectator() = 0;

    inline void add(const double sample);
    inline void clear();
    inline double getMean();
    inline double getVariance();
        
private:
    const boost::shared_ptr<ExpectatorBase> _next;
    boost::accumulators::accumulator_set<double, 
        boost::accumulators::stats<
            boost::accumulators::tag::mean, 
            boost::accumulators::tag::variance> > _accumulator;
            
};


inline void ExpectatorBase::add(const double sample)
{
    _accumulator(sample);
}

inline void ExpectatorBase::clear()
{
    _accumulator = 
        boost::accumulators::accumulator_set<double, 
            boost::accumulators::stats<
                boost::accumulators::tag::mean, 
                boost::accumulators::tag::variance> >();
}

inline double ExpectatorBase::getMean()
{
    return boost::accumulators::mean(_accumulator);
}

inline double ExpectatorBase::getVariance()
{
    return boost::accumulators::variance(_accumulator);
}

