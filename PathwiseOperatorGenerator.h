
class PathwiseOperatorGenerator {
public:
    PathwiseOperatorGenerator();
    virtual ~PathwiseOperatorGenerator();

    virtual void generate(
        const boost::numeric::ublas::matrix<double>& path,
        boost::numeric::ublas::matrix<double>& pathwiseOperator,
        const std::size_t timeIndex) const = 0;

private:
};

