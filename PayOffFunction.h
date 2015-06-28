
class MathFunction 
{
public:
    MathFunction();
    virtual ~MathFunction();

    virtual double operator()(const boost::numeric::ublas::vector<double>& x) = 0;
    virtual  calculateDerivative(
        const boost::numeric::ublas::vector<double>& x,
        boost::numeric::ublas::vector<double>& y) = 0;
 
    
private:
            
};
MathFunction::MathFunction() 
{
    
}
MathFunction::~MathFunction() 
{
}
