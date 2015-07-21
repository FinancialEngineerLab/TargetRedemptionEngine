#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

inline std::size_t invertIndex(
    const std::size_t index, 
    const std::size_t endIndex) {
    return endIndex - 1 - index;
}

inline void initializePath(
    boost::numeric::ublas::matrix<double>& path,
    const boost::numeric::ublas::vector<double>& processes)
{
    boost::numeric::ublas::column(path, 0) = processes;
}


inline void generateRandomsVectorFromIterator(
    boost::numeric::ublas::vector<double>& randoms,
    std::vector<double>::const_iterator& random,
    const std::size_t dimension) 
{
    for (std::size_t dimensionIndex = 0; dimensionIndex < dimension; 
        ++dimensionIndex) {
        randoms[dimensionIndex] = *random;
        ++random;
    }
}

template <typename T>
inline double calculateKronecker(const T x, const T y)
{
    return (x == y ? 1.0 : 0.0);
}

inline double square(const double x) 
{
    return x * x;
}


