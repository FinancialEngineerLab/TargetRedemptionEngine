#include <boost/numeric/ublas/vector.hpp>

class PathwiseOperatorGenerator {
public:
    PathwiseOperatorGenerator();
    virtual ~PathwiseOperatorGenerator();

    virtual void generate(
        const boost::numeric::ublas::vector<double>& state,
        boost::numeric::ublas::matrix<double>& pathwiseOperator,
        const double time, 
        const std::size_t timeStepSize,
        std::vector<double>::iterator random) = 0;

private:
};

