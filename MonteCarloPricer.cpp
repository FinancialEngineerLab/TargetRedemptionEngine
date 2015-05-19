#include "MonteCarloPricer.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
MonteCarloPricer::MonteCarloPricer(
    const boost::shared_ptr<StochasticDifferentialEquation>& model,
    const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator,
    const boost::shared_ptr<PayOff>& payOff)
    :
    _model(model),
    _discretizationScheme(discretizationScheme),
    _randomGenerator(randomGenerator),
    _payOff(payOff)
{
}

MonteCarloPricer::~MonteCarloPricer() 
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
double MonteCarloPricer::simulatePrice(
    const boost::numeric::ublas::vector<double>& spots,
    const double maturity,
    const std::size_t numberOfSimulations,
    const std::size_t numberOfTimeSteps) const
{
    double sumPrice = 0.0;
    const double timeStepSize = maturity / numberOfTimeSteps;
    const std::size_t dimension = _model->getDimension();
    const std::size_t dimensionOfBrownianMotion = 
        _model->getDimensionOfBrownianMotion();

    assert(spots.size() == dimension);
    assert(_randomGenerator->getDimension() == 
        dimensionOfBrownianMotion * numberOfTimeSteps);

    boost::numeric::ublas::vector<double> processes(dimension, 0.0);

    for (std::size_t simulationIndex = 0; simulationIndex < numberOfSimulations;
        ++simulationIndex) {
        processes = simulateOnePath(
            processes, spots, timeStepSize, numberOfTimeSteps);
        sumPrice += _payOff->payOffFunction(processes);
    }

    return sumPrice / numberOfSimulations;
}

/******************************************************************************
 * virtual functions.
 ******************************************************************************/
boost::numeric::ublas::vector<double>& MonteCarloPricer::simulateOnePath(
    boost::numeric::ublas::vector<double>& processes,
    const boost::numeric::ublas::vector<double>& spots,
    const double timeStepSize,
    const std::size_t numberOfTimeSteps) const
{
    double time = 0.0;
    processes = spots;
    std::vector<double> randoms(_randomGenerator->getDimension());
    _randomGenerator->generateNormalRandoms(randoms);
    std::vector<double>::iterator random = randoms.begin();

    for (std::size_t timeIndex = 0; timeIndex <  numberOfTimeSteps; 
        ++timeIndex) {
        _discretizationScheme->simulateOneStep(
            processes, _model, time, timeStepSize, random);

        time += timeStepSize;
    }

    return processes;
}


