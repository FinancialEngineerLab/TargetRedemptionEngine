#include "DifferentiatedDrift.h"

class DifferentiatedLiborMarketModelDrift : public DifferentiatedDrift
{
public:
    DifferentiatedLiborMarketModelDrift();
    virtual ~DifferentiatedLiborMarketModelDrift();

    virtual void calculate(
        const double t,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& results) const;
    
private:
    
};

