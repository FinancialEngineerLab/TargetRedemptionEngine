#ifndef SOLVER_H
#define SOLVER_H

#include "SolverEngine.h"

#include <boost/shared_ptr.hpp>

class Solver {
public:
    Solver();
    ~Solver();

     double solve(
         const double x, 
         const double y,
         const double tolerance,
         const boost::shared_ptr<SolverEngine>& engine);

private:

};

#endif

