#include "FuncitonMathematics.h"

class FunctionCall public FunctionMathematics {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    FuncitonCall(const double strike);
    virtual ~FunctionCall();

    virtual double operator()(
        const boost::numeric::ublas::vector<double>& spot) = 0;
    virtual void calculateDifferential(
        const boost::numeric::ublas::vector<double>& spot,
        boost::numeric::ublas::vector<double>& result) = 0;
    
private:
    const double _strike;
            
};

