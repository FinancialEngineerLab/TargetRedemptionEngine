#include "TimeIndexManager.h"

#include <cassert>

TimeIndexManager::TimeIndexManager(
    const std::vector<double>& observedTimes, 
    const std::vector<std::size_t>& timeIndice) 
    :
    _observedTimes(observedTimes),
    _timeIndice(timeIndice)
{
}

TimeIndexManager::~TimeIndexManager()
{
}

double TimeIndexManager::operator[](const std::size_t index) const
{
    assert(0 <= index);
    assert(index < _observedTimes.size());
    return _observedTimes[_timeIndice[index]];
}

std::size_t TimeIndexManager::size() const
{
    return _timeIndice.size();
}

std::size_t TimeIndexManager::getTimeIndex(const std::size_t index) const
{
    assert(0 <= index);
    assert(index < size());
    return _timeIndice[index];
}

