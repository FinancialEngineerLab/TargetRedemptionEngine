#include "TimeIndexManager.h"

#include <cassert>

TimeIndexManager::TimeIndexManager(
    const std::vector<double>& timeGrid, 
    const std::vector<std::size_t>& timeIndice) 
    :
    _timeGrid(timeGrid),
    _timeIndice(timeIndice)
{
}

TimeIndexManager::~TimeIndexManager()
{
}

double TimeIndexManager::operator[](const std::size_t index) const
{
    assert(0 <= index);
    assert(index < _timeGrid.size());
    return _timeGrid[_timeIndice[index]];
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

std::vector<double> TimeIndexManager::getTimeGrid() const
{
    return _timeGrid;
}


/**
 * @brief get an index which satisfies the following inequality,
 *        time at (index-1) <= time < time at index.
 *        if time < (time at the first index), then return 0.
 *        if time > (time at the last index), then reutn (last index + 1).
 */
std::size_t TimeIndexManager::searchIndex(const double time) const
{
    for (std::size_t timeIndex = 0; timeIndex < _timeIndice.size(); 
        ++timeIndex) {
        if (time < _timeGrid[_timeIndice[timeIndex]]) {
            return timeIndex;
        }
    }

    return _timeIndice.size();
}



