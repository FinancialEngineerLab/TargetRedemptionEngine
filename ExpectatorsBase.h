#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

class ExpectatorsBase {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ExpectatorsBase(
        const boost::shared_ptr<ExpectatorsBase>& next);
    virtual ~ExpectatorsBase();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms) = 0;
    virtual double doExpectators() = 0;

    inline void add(const boost::numeric::ublas::vector<double>& sample);
    inline void clear();
    inline double getMean();
    inline double getVariance();
        
private:
    const boost::shared_ptr<ExpectatorsBase> _next;
    boost::accumulators::accumulator_set<
        boost::numeric::ublas::vector<double>, 
        boost::accumulators::stats<
            boost::accumulators::tag::mean, 
            boost::accumulators::tag::variance> > _accumulator;
};


inline void ExpectatorsBase::add(const boost::numeric::ublas::vector<double>& sample)
{
    _accumulator(sample);
}

inline void ExpectatorsBase::clear()
{
    _accumulator = 
        boost::accumulators::accumulator_set<
            boost::numeric::ublas::vector<double>, 
            boost::accumulators::stats<
                boost::accumulators::tag::mean, 
                boost::accumulators::tag::variance> >();
}

inline double ExpectatorsBase::getMean()
{
    return boost::accumulators::mean(_accumulator);
}

inline double ExpectatorsBase::getVariance()
{
    return boost::accumulators::variance(_accumulator);
}

