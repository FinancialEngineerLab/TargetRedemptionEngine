
class DifferentiatedDrift 
{
public:
    DifferentiatedDrift();
    virtual ~DifferentiatedDrift();

    virtual void calculate(
        const double t,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& results) const = 0;
    
private:
        
};
