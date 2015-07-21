#include "DeltaOperatorGenerator.h"
#include "utilities.h"

#include <vector>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
DeltaOperatorGenerator::DeltaOperatorGenerator(
    const boost::shared_ptr<
        const StochasticDifferentialEquationWithDifferential> model)
    :
    _model(model),
    _differentialDrift(_model->getDimension(), _model->getDimension()),
    _differentialDiffusion(
        boost::extents[_model->getDimension()][_model->getDimension()]
            [_model->getDimensionOfBrownianMotion()])
{
}

DeltaOperatorGenerator::~DeltaOperatorGenerator() 
{
}

void DeltaOperatorGenerator::generate(
    const boost::numeric::ublas::vector<double>& state,
    boost::numeric::ublas::matrix<double>& pathwiseOperator,
    const double time, 
    const std::size_t timeStepSize,
    std::vector<double>::const_iterator& random) 
{
    const std::size_t dimension = _model->getDimension();
    const std::size_t dimensionOfBrownianMotion = 
        _model->getDimensionOfBrownianMotion();

    //randoms
    boost::numeric::ublas::vector<double> randoms(dimensionOfBrownianMotion);
    generateRandomsVectorFromIterator(randoms, random, dimension);

    //caculate differentials.
    _model->calculateDifferentialDrift(time, state, _differentialDrift);
    _model->calculateDifferentialDiffusion(time, state, _differentialDiffusion);

    //add diffusion term
    doTensorContraction(_differentialDiffusion, randoms, 
        pathwiseOperator, sqrt(timeStepSize));

    for (std::size_t rowIndex = 0; rowIndex < pathwiseOperator.size1(); 
        ++rowIndex) {
        for (std::size_t columnIndex = 0; columnIndex < pathwiseOperator.size2(); 
            ++columnIndex) {
            //add drfit term
            pathwiseOperator(rowIndex, columnIndex) += 
                _differentialDrift(rowIndex, columnIndex) * timeStepSize;

            //add kronecker delta
            pathwiseOperator(rowIndex, columnIndex) += 
                calculateKronecker(rowIndex, columnIndex);
        }
    }
}

/******************************************************************************
 * private functions.
 ******************************************************************************/
void DeltaOperatorGenerator::doTensorContraction(
    const boost::multi_array<double, 3>& differentialDiffusion,
    const boost::numeric::ublas::vector<double>& randoms,
    boost::numeric::ublas::matrix<double>& result,
    const double deviation)
{
    typedef boost::multi_array<double, 3> tensor3;

    const boost::multi_array_types::size_type *shape = 
        differentialDiffusion.shape();
        
    assert(shape[2] == randoms.size());

    //tensor row
    for (tensor3::index rowIndex = 0; 
        static_cast<std::size_t>(rowIndex) < shape[0]; ++rowIndex) {
        //tensor column
        for (tensor3::index columnIndex = 0; 
            static_cast<std::size_t>(columnIndex) < shape[1]; ++columnIndex) {
            //tensor depth
            for (tensor3::index depthIndex = 0; 
                static_cast<std::size_t>(depthIndex) < shape[2]; ++depthIndex) {
                    result(rowIndex, columnIndex) += 
                        differentialDiffusion[rowIndex][columnIndex][depthIndex] 
                            * randoms[depthIndex] * deviation;
            }   
        }   
    }   

}


