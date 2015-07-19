#include "DifferentialLiborMarketModelDiffusion.h"

DifferentialLiborMarketModelDiffusion::DifferentialLiborMarketModelDiffusion() 
{
    
}

DifferentialLiborMarketModelDiffusion::~DifferentialLiborMarketModelDiffusion() 
{
}


void DifferentialLiborMarketModelDiffusion::calculate(
    const double time,
    const boost::numeric::ublas::vector<double>& states,
    boost::multi_array<double, 3>& result) const
{
    typedef boost::multi_array<double, 3> tensor3;

    const boost::multi_array_types::size_type *shape = result.shape();

    for (tensor3::index rowIndex = 0; static_cast<std::size_t>(rowIndex) < shape[0]; ++rowIndex) {
        for (tensor3::index columnIndex = 0; static_cast<std::size_t>(columnIndex) < shape[1]; ++columnIndex) {
            for (tensor3::index depthIndex = 0; static_cast<std::size_t>(depthIndex) < shape[2]; ++depthIndex) {
                result[rowIndex][columnIndex][depthIndex] = 0.0;
            }
        }
    }

}

