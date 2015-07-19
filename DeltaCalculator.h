#include "DeltaStrategy.h"

#include <boost/shared_ptr.hpp>

class DeltaCalculator 
{
public:
    DeltaCalculator(
        const boost::shared_ptr<const DeltaStrategy> deltaStrategy);
    ~DeltaCalculator();

    void calculate(boost::numeric::ublas::vector<double>& delta);
    
private:
    const boost::shared_ptr<const DeltaStrategy> _deltaStrategy;
        
};

