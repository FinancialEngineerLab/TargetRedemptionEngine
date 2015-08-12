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


inline std::size_t ufloor(const double x)
{
    return static_cast<std::size_t>(floor(x));
}

inline double logarithmicIntegral(const double x) {
    const double Gamma = 0.577215664901532860606512090082402431042;
    double sum = 0.0;
    double sum1 = 0.0;
    double fractorial = 0.0;
    int sign = 1;
    sum += Gamma + log(log(x));
    for (std::size_t index1 = 1; index1 < 10; ++index1) {
        sum1 = 0.0;
        for (std::size_t index2 = 0; index2 < ufloor((index1-1.0)/2.0); ++index2) {
            sum1 += 1.0 / (2.0 * index2 + 1.0);
        }
        fractorial *= index1;
        sum += sign * sqrt(x) * pow(log(x), index1) * sum1 / (fractorial * pow(2.0, index1-1.0));
        sign *= -1;
    }
    return sum;
}

