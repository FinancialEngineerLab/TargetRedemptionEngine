#include "DeltaOperatorGenerator.h"

DeltaOperatorGenerator::DeltaOperatorGenerator() 
{
}

DeltaOperatorGenerator::~DeltaOperatorGenerator() 
{
}

void DeltaOperatorGenerator::generate(
    const boost::numeric::ublas::matrix<double>& path,
    boost::numeric::ublas::matrix<double>& pathwiseOperator,
    const std::size_t timeIndex) const
{
    for (std::size_t rowIndex = 0; rowIndex < pathwiseOperator.size1(); ++rowIndex) {
        for (std::size_t columnIndex = 0; columnIndex < pathwiseOperator.size2(); ++columnIndex) {
            pathwiseOperator(rowIndex, columnIndex) = calculateOperatorElement(rowIndex, columnIndex);
        }
    }
}
    
