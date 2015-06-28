
class DeltaStrategy 
{
public:
    DeltaStrategy();
    virtual ~DeltaStrategy();

    virtual void calculate(boost::numeric::ublas::vector<double>& delta) = 0;
private:
        
};

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
DeltaStrategy::DeltaStrategy() 
{
    
}

DeltaStrategy::~DeltaStrategy() 
{
}

