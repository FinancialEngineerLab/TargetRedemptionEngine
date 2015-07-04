class PathwiseDeltaCalculator : public SampleCalculator
{
public:
    PathwiseDeltaCalculator();
    virtual ~PathwiseDeltaCalculator();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/   
    virtual double operator()(
        const boost::numeric::ublas::matrix<double>& path) const;
private:
            
};

