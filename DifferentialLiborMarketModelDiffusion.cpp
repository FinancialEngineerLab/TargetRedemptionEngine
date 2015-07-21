#include "DifferentialLiborMarketModelDiffusion.h"

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
DifferentialLiborMarketModelDiffusion::DifferentialLiborMarketModelDiffusion() 
{
    
}

DifferentialLiborMarketModelDiffusion::~DifferentialLiborMarketModelDiffusion() 
{
}


/**
 * @params result  Assuming b is the diffusion function of the LMM,
 *                 result[row][column][depth] means 
 *                 \frac{\partial b_{row, depth}}{\partial x_{column}}.
 */
void DifferentialLiborMarketModelDiffusion::calculate(
    const double time,
    const boost::numeric::ublas::vector<double>& states,
    boost::multi_array<double, 3>& result) const
{
    typedef boost::multi_array<double, 3> tensor3;

    const boost::multi_array_types::size_type *shape = result.shape();

    //row
    for (tensor3::index rowIndex = 0; 
        static_cast<std::size_t>(rowIndex) < shape[0]; ++rowIndex) {
        //column
        for (tensor3::index columnIndex = 0; 
            static_cast<std::size_t>(columnIndex) < shape[1]; ++columnIndex) {
            //depth
            for (tensor3::index depthIndex = 0; 
                static_cast<std::size_t>(depthIndex) < shape[2]; ++depthIndex) {
                result[rowIndex][columnIndex][depthIndex] = 0.0;
            }
        }
    }

}

