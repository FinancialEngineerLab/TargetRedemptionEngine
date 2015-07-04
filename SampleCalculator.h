class SampleCalculator 
{
public:
    SampleCalculator();
    virtual ~SampleCalculator();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const = 0;
private:
            
};

