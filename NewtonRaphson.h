#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

#include "SolverEngine.h"
#include "FunctionMathematics.h"

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

class NewtonRaphson : public SolverEngine {
public:
    NewtonRaphson(
        const boost::function<double(double)>& function,
        const boost::function<double(double)>& differential);
    virtual ~NewtonRaphson();

    virtual double update(
        const double x, 
        const double y);
    virtual bool isConverged(
        const double x, 
        const double y,
        const double tolerance);
private:
    const boost::function<double(double)> _function;
    const boost::function<double(double)> _differential;
};


#endif
