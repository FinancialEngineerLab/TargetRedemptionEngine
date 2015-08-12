#pragma once

#include "DiscretizationScheme.h"

/**
 * @brief The class only supports 1-dim processes.
 */
class PredictorCorrector : public DiscretizationScheme {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    PredictorCorrector(
        const std::size_t dimensionOfBrownianMotion,
        const double theta,
        const double eta);
    virtual ~PredictorCorrector();

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
    const double _eta;
    const double _theta;
    //! cache
    boost::numeric::ublas::vector<double> _drift;
    //! cache
    boost::numeric::ublas::matrix<double> _diffusion;
    //! cache
    boost::numeric::ublas::vector<double> _cacheProcess1;
    //! cache
    boost::numeric::ublas::vector<double> _cacheProcess2;

    double calculateDriftEta(
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const double time,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::vector<double>& drift);
    
};

