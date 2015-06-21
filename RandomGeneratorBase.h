#pragma once

#include <vector>

class RandomGeneratorBase {
public:

    RandomGeneratorBase(const std::size_t dimension);
    virtual ~RandomGeneratorBase();

    inline std::size_t getDimension() const;
    virtual void resetDimension(const std::size_t dimension);

    virtual void generateUniformRandoms(std::vector<double>& randoms) = 0;
    virtual void generateNormalRandoms(std::vector<double>& randoms) = 0;
    virtual void skip(const std::size_t numberOfPaths) = 0;
    virtual void setSeed(const std::size_t seed) = 0;
    virtual void reset() = 0;

private:
    std::size_t _dimension;
};

std::size_t RandomGeneratorBase::getDimension() const
{
    return _dimension;
}
