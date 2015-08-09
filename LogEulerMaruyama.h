#pragma once

#include "DiscretizationScheme.h"

/**
 * @brief The class only supports 1-dim processes.
 */
class LogEulerMaruyama : public DiscretizationScheme {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    LogEulerMaruyama(
        const std::size_t dimensionOfBrownianMotion);
    virtual ~LogEulerMaruyama();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void simulateOneStep(
        boost::numeric::ublas::vector<double>& processes, 
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const double time,
        const double timeStepSize,
        std::vector<double>::const_iterator& random);

private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    //! cache
    boost::numeric::ublas::vector<double> _drift;
    //! cache
    boost::numeric::ublas::matrix<double> _diffusion;
    //! cache
    boost::numeric::ublas::vector<double> _cacheProcess;
    
};

