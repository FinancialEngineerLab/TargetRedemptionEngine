#pragma once

#include "DiscretizationScheme.h"

class EulerMaruyama 
    : public DiscretizationScheme {
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    EulerMaruyama();
    virtual ~EulerMaruyama();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void simulateOneStep(
        boost::numeric::ublas::vector<double>& processes, 
        const boost::shared_ptr<const StochasticDifferentialEquation>& model,
        const double time,
        const double timeStepSize,
        std::vector<double>::iterator& random) const;

private:
    /**************************************************************************
     * private functions.
     **************************************************************************/
    void generateRandomsVectorFromIterator(
        boost::numeric::ublas::vector<double>& randoms,
        std::vector<double>::iterator& random,
        const std::size_t dimension) const;
            
};

