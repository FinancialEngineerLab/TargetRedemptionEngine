#include "Solver.h"

#include <iostream>

Solver::Solver()
{
    
}
Solver::~Solver() 
{
}

/**
 * @brief 
 * @param x 
 * @param y
 */
double Solver::solve(
    const double x, 
    const double y,
    const double tolerance,
    const boost::shared_ptr<SolverEngine>& engine)
{
    double oldX = x;
    double newX = 0.0;

    while (!engine->isConverged(oldX, y, tolerance)) {
        newX = engine->update(oldX, y);
        oldX = newX;
    }

    return oldX;
}

