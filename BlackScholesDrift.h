#pragma once

#include "Drift.h"

class BlackScholesDrift :
    public Drift {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    BlackScholesDrift(const double interestRate, const double dividend);
    virtual ~BlackScholesDrift();
        
    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const;

private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const double _interestRate;
    const double _dividend;
};

class LogBlackScholesDrift :
    public Drift {
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    LogBlackScholesDrift(const double interestRate, 
        const double dividend, const double volatility);
    virtual ~LogBlackScholesDrift();
        
    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift) const;

private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const double _interestRate;
    const double _dividend;
    const double _volatility;
};
