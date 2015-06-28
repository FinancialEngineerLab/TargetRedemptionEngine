
class DeltaBumpStrategy : public DeltaStrategy
{
public:
    DeltaBumpStrategy(
        const boost::numeric::ublas::vector<double>& shock,
        const boost::shared_ptr<const MonteCarloPricer>& pricer);
    virtual ~DeltaBumpStrategy();
    
    virtual void calculate(boost::numeric::ublas::vector<double>& delta);

private:
    const boost::numeric::ublas::vector<double> _shock;
    const boost::shared_ptr<const MonteCarloPricer> _pricer;
            
};


DeltaBumpStrategy::DeltaBumpStrategy(
    const boost::numeric::ublas::vector<double>& shock,
    const boost::shared_ptr<const MonteCarloPricer> pricer) 
    :
    _shock(shock),
    _pricer(pricer)
{
    
}

DeltaBumpStrategy::~DeltaBumpStrategy() 
{
}
