#pragma once


class FunctionMathematics {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    FunctionMathematics();
    virtual ~FunctionMathematics();

    virtual double operator()(const boost::numeric::ublas::vector<double>& x) = 0;
    virtual void calculateDerivative(
        const boost::numeric::ublas::vector<double>& x,
        boost::numeric::ublas::vector<double>& result) = 0;
 
    
private:
            
};

