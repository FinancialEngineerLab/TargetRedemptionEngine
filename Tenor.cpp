#include "Tenor.h"

#include <cassert>

Tenor::Tenor(
    const boost::shared_ptr<Maturities>& maturities,
    const std::vector<std::size_t>& tenorToMaturityIndice)
    :
    _maturities(maturities),
    _tenorToMaturityIndice(tenorToMaturityIndice)
{
}

Tenor::~Tenor()
{
}

double Tenor::operator[](const std::size_t index) const
{
    assert(0 <= index < _tenorToMaturityIndice.size());
    return _maturities->operator[](_tenorToMaturityIndice[index]);
}

std::size_t Tenor::size() const
{
    return _tenorToMaturityIndice.size();
}

std::size_t Tenor::getAssetIndex(const std::size_t index) const
{    
    return _maturities->getAssetIndex(_tenorToMaturityIndice[index]);
}

std::size_t Tenor::getTimeIndex(const std::size_t index) const
{    
    return _maturities->getTimeIndex(_tenorToMaturityIndice[index]);
}

