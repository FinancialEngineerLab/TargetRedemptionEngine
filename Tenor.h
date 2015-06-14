#pragma once

#include "TimeIndexManager.h"
#include "Maturities.h"

class Tenor 
{
public:
    Tenor(
        const boost::shared_ptr<Maturities>& maturities, 
        const std::vector<std::size_t>& tenorToMaturityIndice);
    ~Tenor();

    double operator[](const std::size_t index) const;
    std::size_t size() const;
    std::size_t getAssetIndex(const std::size_t index) const;
    std::size_t getTimeIndex(const std::size_t index) const;
    
private:
    const boost::shared_ptr<const Maturities> _maturities;
    const std::vector<std::size_t> _tenorToMaturityIndice;
            
};
