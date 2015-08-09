#pragma once

#include "DiscretizationScheme.h"

class EulerMaruyama 
    : public DiscretizationScheme {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    EulerMaruyama(
        const std::size_t dimensionOfBrownianMotion);
    virtual ~EulerMaruyama();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void simulateOneStep(
        boost::numeric::ublas::vector<double>& process, 
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const double time,
        const double timeStepSize,
        std::vector<double>::const_iterator&  random);

private:
    boost::numeric::ublas::vector<double> _drift;
    boost::numeric::ublas::matrix<double> _diffusion;
            
};

