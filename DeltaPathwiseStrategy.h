
class DeltaPathwiseStrategy : public DeltaStrategy
{
public:
    DeltaPathwiseStrategy();
    virtual ~DeltaPathwiseStrategy();

    virtual void calculate(boost::numeric::ublas::vector<double>& delta);
    
private:
    const boost::shared_ptr<const MathFunction> _payOffFunction;
    const boost::shared_ptr<const PathSimulator> _pathSimulator;
    const boost::shared_ptr<const PathwiseOperation> _operation;
    const boost::shared_ptr<const PathwiseOperatorCalculator> _operatorCalculator;
    const std::size_t _numberOfSimulation;
            
};

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
DeltaPathwiseStrategy::DeltaPathwiseStrategy() 
{
    
}
DeltaPathwiseStrategy::~DeltaPathwiseStrategy() 
{
}

DeltaPathwiseStrategy::calculate(
    boost::numeric::ublas::vector<double>& delta)
{
    boost::numeric::ublas::matrix<double> path(0, 0);
    for (std::size_t simulationIndex = 0; simulationIndex < _numberOfSimulation;
        simulationIndex++) {
        _pathSimulator->simulateOnePath(processess, path, observedTimes);

        calculate(path, delta, _payOffFunction);
    }
}

DeltaPathwiseStrategy::backward(
    boost::numeric::ublas::vector<double>& path,
    boost::numeric::ublas::vector<double>& delta)
{
    if (_isAdjoint) {
        _payOffFunction->differentiate(path, derivateive);
        step = prod(derivative, operatorMatrix);
        //number of timesteps
        for () {
            _operatorCalculator(path, operatorMatrix, index);

            step = prod(step, operatorMatrix);
        }
    } else {
        //number of timesteps
        for () {
            
        }

    }
}
