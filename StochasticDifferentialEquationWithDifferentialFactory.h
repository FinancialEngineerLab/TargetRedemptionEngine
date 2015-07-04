
class StochasticDifferentialEquationWithDifferentialFactory :
    public StochasticDifferentialEquationFactory
{
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    StochasticDifferentialEquationWithDifferentialFactory();
    virtual ~StochasticDifferentialEquationWithDifferentialFactory();

    /**************************************************************************
     * member functions
     **************************************************************************/
    boost::shared_ptr<const StochasticDifferentialEquationWithDifferential> 
        makeStochasticDifferentialEquationWithDifferential() const;
    
private:
    const boost::shared_ptr<const StochasticDifferentialEquationFactory>
        _factory;

    virtual boost::shared_ptr<DifferentialDrift> 
        makeDifferentialDrift() const = 0;
    virtual boost::shared_ptr<DifferentialDiffusion> 
        makeDifferentialDiffusion() const = 0;
        
};

