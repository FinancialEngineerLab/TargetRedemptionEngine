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
    const std::size_t timeIndex,
    std::vector<double>& randoms) const
{
    boost::numeric::ublas::matrix<double> differentiaDrift(0, 0, 0.0);
    sde->differentialDrift(time, state, diffirentialDrift);
    boost::numeric::ublas::matrix<double> differentialDiffusion(0, 0, 0.0);

    for (std::size_t rowIndex = 0; rowIndex < pathwiseOperator.size1(); ++rowIndex) {
        sde->differentialDiffusion(time, state, rowIndex, diffirentialDiffusion);
        for (std::size_t columnIndex = 0; columnIndex < pathwiseOperator.size2(); ++columnIndex) {
            pathwiseOperator(rowIndex, columnIndex) = 
                calculateOperatorElement(rowIndex, columnIndex, 
                    differentialDrfit, differentialDiffusion, randoms);
        }
    }
}

double DeltaOperatorGenerator::calculateOperatorElement(
    const std::size_t rowIndex,
    const std::size_t columnIndex,
    const boost::numeric::ublas::matrix<double>& diffirentialDrift,
    const boost::numeric::ublas::matrix<double>& differentialDiffusion,
    std::vector<double>& randoms)
{
    double kronecker = (rowIndex == columnIndex ? 1.0 : 0.0);

    double driftTerm = 0.0; 
    driftTerm = differentialDrfit(rowIndex, columnIndex) * timeStepSize;

    double diffusionTerm = 0.0;
    for (std::size_t randomIndex = 0; randomIndex < _sde->getDimensionOfBrownianMotion();
        ++randomIndex) {
        diffusionTerm += differentialDiffusion(randomIndex, columnIndex) 
            * randoms[randomIndex] * sqrt(timeStepSize);
    }
    return kronecker + driftTerm + diffusionTerm;
}

    
