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

/**
 * @brief get an index which satisfies the following inequality,
 *        time at index <= time < time at (index + 1).
 *        if time < time at the first index, then return -1.
 *        if time > time at the last index, then reutn (last index + 1).
 */
int TimeIndexManager::searchIndex(const double time) const
{
    for (std::size_t timeIndex = 0; timeIndex < _timeIndice.size(); ++timeIndex) {
        if (time < _observedTimes[_timeIndice[timeIndex]]) {
            return timeIndex - 1;
        }
    }
    return _timeIndice.size();
}

