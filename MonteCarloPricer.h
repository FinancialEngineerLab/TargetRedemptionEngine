#pragma once

#include "StochasticDifferentialEquation.h"
#include "DiscretizationScheme.h"
#include "RandomGeneratorBase.h"
#include "PlainVanillaPayOff.h"

class MonteCarloPricer 
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    MonteCarloPricer(
        const boost::shared_ptr<StochasticDifferentialEquation>& model,
        const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
        const boost::shared_ptr<RandomGeneratorBase>& randomGenerator,
        const boost::shared_ptr<PayOff>& payOff);
    virtual ~MonteCarloPricer();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    double simulatePrice(
        const boost::numeric::ublas::vector<double>& spots,
        const double maturity,
        const std::size_t numberOfSimulations,
        const std::size_t numberOfTimeSteps) const;
    
    /******************************************************************************
     * virtual functions.
     ******************************************************************************/
    virtual boost::numeric::ublas::vector<double>& simulateOnePath(
        boost::numeric::ublas::vector<double>& processes,
        const boost::numeric::ublas::vector<double>& spots,
        const double timeStepSize,
        const std::size_t numberOfTimeSteps) const;
private:
    /******************************************************************************
     * private variables.
     ******************************************************************************/
    const boost::shared_ptr<StochasticDifferentialEquation>& _model;
    const boost::shared_ptr<DiscretizationScheme>& _discretizationScheme;
    const boost::shared_ptr<RandomGeneratorBase>& _randomGenerator;
    const boost::shared_ptr<PayOff>& _payOff;

};



