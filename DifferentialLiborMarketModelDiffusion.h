#pragma once

#include "DifferentialDiffusion.h"

class DifferentialLiborMarketModelDiffusion : public DifferentialDiffusion
{
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    DifferentialLiborMarketModelDiffusion();
    virtual ~DifferentialLiborMarketModelDiffusion();

    virtual void calculate(
        const double time,
        const boost::numeric::ublas::vector<double>& states,
        boost::multi_array<double, 3>& results) const;
    
private:
    
            
};
