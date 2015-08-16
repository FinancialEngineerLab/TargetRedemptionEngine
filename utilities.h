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

//! integrate 1/(A + B * ln(y / C)) from 0 to x w.r.t. y
inline double logarithmicIntegralChangeOfVariable(
    const double x,
    const double A,
    const double B,
    const double C) {
    //change of variables to transfrom integrand 1/ln(x)
    const double to = exp(A) * pow(x / C, B);
    return logarithmicIntegral(to) * exp(1.0 / B);
}

inline double logarithmicIntegralStep(
    const double state,
    const double strike1,
    const double strike2,
    const double volatility1,
    const double volatility2)
{
    assert(strike2 >= strike1);
    assert(volatility2 >= volatility1);

    const double D = log(strike2 /strike1) ;
    const double A = D * strike1;
    const double B = volatility2 - volatility1; 
    const double C = volatility1;
    const double x = exp(A) * pow(state/C, B);
    
    return D *  logarithmicIntegralChangeOfVariable(x, A, B, C);
}

