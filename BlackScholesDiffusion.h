#pragma once

#include "Diffusion.h"

class BlackScholesDiffusion 
    : public Diffusion
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    BlackScholesDiffusion(const double volatility);
    virtual ~BlackScholesDiffusion();

    /**************************************************************************
     * inherited  operators.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const;

private:
    /**************************************************************************
     * private variables
     **************************************************************************/
    const double _volatility;
};


class LogBlackScholesDiffusion 
    : public Diffusion
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    LogBlackScholesDiffusion(const double volatility);
    virtual ~LogBlackScholesDiffusion();

    /**************************************************************************
     * inherited  operators.
     **************************************************************************/
    virtual void operator()(
        const double time, 
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& diffusion) const;

private:
    /**************************************************************************
     * private variables
     **************************************************************************/
    const double _volatility;
};

