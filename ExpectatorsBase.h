#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <vector>

#define BOOST_NUMERIC_FUNCTIONAL_STD_VECTOR_SUPPORT 

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
        const std::size_t dimension);
    virtual ~ExpectatorsBase();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void addSample(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms) = 0;
    virtual void doExpectation(
        boost::numeric::ublas::vector<double>& result) = 0;

    virtual void add(const boost::numeric::ublas::vector<double>& sample);
    virtual void clear();
    virtual void getMean(
        boost::numeric::ublas::vector<double>& result);
    virtual void getVariance(
        boost::numeric::ublas::vector<double>& result);
        
private:
    const std::size_t _dimension;
    std::vector<double> _cache;

    boost::accumulators::accumulator_set<
        std::vector<double>, 
        boost::accumulators::stats<
            boost::accumulators::tag::mean, 
            boost::accumulators::tag::variance> > _accumulator;
};


