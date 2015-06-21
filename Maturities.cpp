#include "Maturities.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
Maturities::Maturities(
    const std::vector<double>& observedTimes,
    const std::vector<std::size_t>& maturityIndice)
    :
    _maturities(boost::shared_ptr<TimeIndexManager>(
        new TimeIndexManager(observedTimes, maturityIndice)))
{
}

Maturities::~Maturities()
{
}

double Maturities::operator[](const std::size_t index) const
{
    return _maturities->operator[](index);
}

std::size_t Maturities::size() const
{
    return _maturities->size();
}

std::size_t Maturities::getAssetIndex(const std::size_t index) const
{    
    return index;
}

//!To get the index in observedTimes
std::size_t Maturities::getTimeIndex(const std::size_t index) const
{    
    return _maturities->getTimeIndex(index);
}

std::size_t Maturities::findIndexIncludingTime(const double time) const
{    
    if ((*this)[0] > time) {
        return 0UL;
    }
    for (std::size_t maturityIndex = 0; maturityIndex < size(); ++maturityIndex) {
        if ((*this)[maturityIndex] > time) {
            return maturityIndex + 1;
        }
    }
    return size();
}

