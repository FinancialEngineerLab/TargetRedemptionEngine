
class DeltaPathwiseStrategy : public DeltaStrategy {
public:
    DeltaPathwiseStrategy();
    virtual ~DeltaPathwiseStrategy();

    virtual void calculate(boost::numeric::ublas::vector<double>& delta);
    
private:
    const boost::shared_ptr<const SampleCalculator> _sampleCalculator;
    const boost::shared_ptr<const MathFunction> _payOffFunction;
    const boost::shared_ptr<const PathSimulator> _pathSimulator;
    const std::size_t _numberOfSimulation;
            
};

