#include "DifferentiatedDiffusion.h"

class DifferentiatedLiborMarketModelDiffusion : public DifferentiatedDiffusion
{
public:
    DifferentiatedLiborMarketModelDiffusion();
    virtual ~DifferentiatedLiborMarketModelDiffusion();

    virtual void calculate(
        const double t,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& results) const;
    
private:
            
};
