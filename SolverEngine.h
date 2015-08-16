#ifndef SOLVER_ENGINE_H
#define SOLVER_ENGINE_H

class SolverEngine 
{
public:
    SolverEngine();
    virtual ~SolverEngine();

    virtual double update(const double x, const double y) = 0;
    virtual bool isConverged(
        const double x, 
        const double y,
        const double tolerance) = 0;

private:
        
};


#endif

