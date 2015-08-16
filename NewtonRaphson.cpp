#include "NewtonRaphson.h"<`0`>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
/**
 * @brief TODO:accept multi-variate funciton.
 */
NewtonRaphson::NewtonRaphson(
    const boost::function<double(double)>& function,
    const boost::function<double(double)>& differential)
    :
    _function(function),
    _differential(differential)
{
}

NewtonRaphson::~NewtonRaphson() 
{
}

double NewtonRaphson::update(const double x, const double y)
{
    const double y0 = _function(x);
    const double gradient = _differential(x);

    return (y - y0) /gradient + x; 
}

bool NewtonRaphson::isConverged(
    const double x, 
    const double y,
    const double tolerance)
{
   const double y0 = _function(x); 

   return (abs(y0 - y) < tolerance);
}

