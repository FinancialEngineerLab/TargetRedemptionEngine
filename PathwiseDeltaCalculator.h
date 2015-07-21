#pragma once

#include "PathwiseOperatorGenerator.h"
#include "SampleCalculator.h"
#include "FunctionMathematics.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class PathwiseDeltaCalculator : public SampleCalculator {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    PathwiseDeltaCalculator(
        const std::size_t timeLength,
        const std::size_t dimension,
        const boost::shared_ptr<PathwiseOperatorGenerator>& _generator,
        const boost::shared_ptr<FunctionMathematics>& payOffFunction);
    ~PathwiseDeltaCalculator();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void operator()(
        const boost::numeric::ublas::matrix<double>& path,
        const std::vector<double>& observedTimes,
        const std::vector<double>& randoms,
        boost::numeric::ublas::vector<double>& result) const;

private:
    std::vector< boost::shared_ptr< boost::numeric::ublas::matrix<double> > > 
        _pathwiseOperators;
    const boost::shared_ptr<PathwiseOperatorGenerator> _generator;
    const boost::shared_ptr<FunctionMathematics> _payOffFunction; 
};

