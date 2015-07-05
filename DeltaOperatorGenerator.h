#include "PathwiseOperatorGenerator.h"

class DeltaOperatorGenerator : public PathwiseOperatorGenerator
{
public:
    DeltaOperatorGenerator();
    virtual ~DeltaOperatorGenerator();

    virtual void generate(
        const boost::numeric::ublas::matrix<double>& path,
        boost::numeric::ublas::matrix<double>& pathwiseOperator,
        const std::size_t timeIndex) const;
    
private:
    const boost::shared_ptr<const StochasticDifferentialEquationWithDifferential> 
        _stochasticDifferentiaEquationWithDifferential;
};

