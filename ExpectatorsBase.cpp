#include "ExpectatorsBase.h"

#include <boost/make_shared.hpp>


template <typename T1, typename T2>
void convertData(
    const T1& originatedData,
    T2& destinatedData)
{
    assert(originatedData.size() == destinatedData.size());

    for (std::size_t index = 0; index < originatedData.size(); ++index) {
        destinatedData[index] = originatedData[index];
    }
} 

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ExpectatorsBase::ExpectatorsBase(
    const std::size_t dimension)
    :
    _dimension(dimension),
    _cache(dimension),
    _accumulator(std::vector<double>(dimension))
{
}

ExpectatorsBase::~ExpectatorsBase() 
{
}


void ExpectatorsBase::add(const boost::numeric::ublas::vector<double>& sample)
{
    convertData<
        boost::numeric::ublas::vector<double>, 
        std::vector<double> >(sample, _cache);
    _accumulator(_cache);
}

void ExpectatorsBase::clear()
{
    _accumulator = 
        boost::accumulators::accumulator_set<
            std::vector<double>, 
            boost::accumulators::stats<
                boost::accumulators::tag::mean, 
                boost::accumulators::tag::variance> 
                    >(std::vector<double>(_dimension));
}

void ExpectatorsBase::getMean(
    boost::numeric::ublas::vector<double>& result)
{
    _cache = boost::accumulators::mean(_accumulator);
    convertData<
        std::vector<double>,
        boost::numeric::ublas::vector<double> >(_cache, result);
}

void ExpectatorsBase::getVariance(
    boost::numeric::ublas::vector<double>& result)
{
    _cache = boost::accumulators::variance(_accumulator);
    convertData<
        std::vector<double>,
        boost::numeric::ublas::vector<double> >(_cache, result);
}

