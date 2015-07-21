#pragma once

#include "PathwiseOperatorGenerator.h"
#include "StochasticDifferentialEquationWithDifferential.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/multi_array.hpp>

class DeltaOperatorGenerator : public PathwiseOperatorGenerator {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    DeltaOperatorGenerator(
        const boost::shared_ptr<
            const StochasticDifferentialEquationWithDifferential> model);
    virtual ~DeltaOperatorGenerator();

    virtual void generate(
        const boost::numeric::ublas::vector<double>& state,
        boost::numeric::ublas::matrix<double>& pathwiseOperator,
        const double time, 
        const std::size_t timeStepSize,
        std::vector<double>::const_iterator& random); 
    
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/
    const boost::shared_ptr<const StochasticDifferentialEquationWithDifferential> 
        _model;
    boost::numeric::ublas::matrix<double> _differentialDrift;
    boost::multi_array<double, 3> _differentialDiffusion;

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    void doTensorContraction(
        const boost::multi_array<double, 3>& differentialDiffusion,
        const boost::numeric::ublas::vector<double>& randoms,
        boost::numeric::ublas::matrix<double>& result,
        const double deviation);
};

