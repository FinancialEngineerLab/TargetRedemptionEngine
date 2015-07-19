#include <boost/numeric/ublas/vector.hpp>

class DeltaStrategy 
{
public:
    DeltaStrategy();
    virtual ~DeltaStrategy();

    virtual void calculate(
        boost::numeric::ublas::vector<double>& delta) const = 0;
private:
        
};

