#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

inline std::size_t invertIndex(std::size_t index, std::size_t endIndex) {
    return endIndex - 1 - index;
}

inline void initializePath(
    boost::numeric::ublas::matrix<double>& path,
    const boost::numeric::ublas::vector<double>& processes)
{
    boost::numeric::ublas::column(path, 0) = processes;
}


void generateRandomsVectorFromIterator(
    boost::numeric::ublas::vector<double>& randoms,
    std::vector<double>::iterator random,
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


void printM(boost::numeric::ublas::matrix<double>& matrix) {
    for (std::size_t row = 0; row < matrix.size1(); ++row) {
        for (std::size_t column = 0; column < matrix.size2(); ++column) {
            std::cout << matrix(row, column) << " ";
        }
        std::cout << std::endl;
    }
}

