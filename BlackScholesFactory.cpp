#include "BlackScholesFactory.h"
#include "BlackScholesDrift.h"
#include "BlackScholesDiffusion.h"

#include <boost/make_shared.hpp>

/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
BlackScholesFactory::BlackScholesFactory(const double interestRate, 
        const double dividend, const double volatility)
    :
    _interestRate(interestRate),
    _dividend(dividend),
    _volatility(volatility),
    _dimension(1),
    _dimensionOfBrownianMotion(1)
{
}

BlackScholesFactory::~BlackScholesFactory()
{
}

/******************************************************************************
 * inherited pure virtual functions
 ******************************************************************************/
boost::shared_ptr<Drift> BlackScholesFactory::makeDrift() const
{
    return boost::shared_ptr<BlackScholesDrift>(
            new BlackScholesDrift(_interestRate, _dividend));
}

boost::shared_ptr<Diffusion> BlackScholesFactory::makeDiffusion() const
{
    return boost::shared_ptr<BlackScholesDiffusion>(
            new BlackScholesDiffusion(_volatility));
}

std::size_t BlackScholesFactory::makeDimension() const
{
    return _dimension;
}
std::size_t BlackScholesFactory::makeDimensionOfBrownianMotion() const
{
    return _dimensionOfBrownianMotion;
}
boost::shared_ptr<boost::numeric::ublas::matrix<double>> 
    BlackScholesFactory::makeCorrelationMatrix() const
{
    return boost::shared_ptr<boost::numeric::ublas::matrix<double>>(
        createCorrelationMatrix());
}
boost::numeric::ublas::matrix<double>* 
    BlackScholesFactory::createCorrelationMatrix() const
{
    return 
}


/******************************************************************************
 * Constructers and Destructers
 ******************************************************************************/
LogBlackScholesFactory::LogBlackScholesFactory(const double interestRate,
        const double dividend, const double volatility)
    :
    _interestRate(interestRate),
    _dividend(dividend),
    _volatility(volatility),
    _dimension(1),
    _dimensionOfBrownianMotion(1)
{
}

LogBlackScholesFactory::~LogBlackScholesFactory()
{
}

/******************************************************************************
 * inherited pure virtual functions
 ******************************************************************************/
boost::shared_ptr<Drift> LogBlackScholesFactory::makeDrift() const
{
    return boost::shared_ptr<LogBlackScholesDrift>(
        new LogBlackScholesDrift(_interestRate, _dividend, _volatility));
}

boost::shared_ptr<Diffusion> LogBlackScholesFactory::makeDiffusion() const
{
    return boost::shared_ptr<LogBlackScholesDiffusion>(
        new LogBlackScholesDiffusion(_volatility));
}

std::size_t LogBlackScholesFactory::makeDimension() const
{
    return _dimension;
}
std::size_t LogBlackScholesFactory::makeDimensionOfBrownianMotion() const
{
    return _dimensionOfBrownianMotion;
}
