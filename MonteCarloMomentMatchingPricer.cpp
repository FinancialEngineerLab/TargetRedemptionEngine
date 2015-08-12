#include "MonteCarloMomentMatchingPricer.h"
#include "utilities.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructer.
 ******************************************************************************/
MonteCarloMomentMatchingPricer::MonteCarloMomentMatchingPricer(
    const boost::shared_ptr<StochasticDifferentialEquation>& model, 
    const boost::shared_ptr<DiscretizationScheme>& discretizationScheme,
    const boost::shared_ptr<MomentMatcher>& momentMatcher,
    const boost::shared_ptr<PresentValueCalculatorMomentMatching>& 
        presentValueCalculator,
    const boost::shared_ptr<RandomGeneratorBase>& randomGenerator)
    :
    _model(model),
    _discretizationScheme(discretizationScheme),
    _momentMatcher(momentMatcher),
    _presentValueCalculator(presentValueCalculator),
    _randomGenerator(randomGenerator)
{
}

MonteCarloMomentMatchingPricer::~MonteCarloMomentMatchingPricer() 
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
double MonteCarloMomentMatchingPricer::simulatePrice(
    const double spot,
    const std::size_t numberOfSimulations,
    const std::vector<double>& timeGrid) const
{
    namespace ublas = boost::numeric::ublas;
    ublas::vector<double> process(1, spot);
    ublas::vector<double> samples(numberOfSimulations, spot);
    std::vector<double> presentValues(numberOfSimulations, 0.0);

    std::vector<double> randoms(_randomGenerator->getDimension());

    for (std::size_t timeIndex = 0; timeIndex < timeGrid.size(); ++timeIndex) {
        std::vector<double>::const_iterator random = randoms.begin();
        const double time = timeGrid[timeIndex];
        const double timeStepSize = timeGrid[timeIndex + 1] - timeGrid[timeIndex];

        //generate sample at a step.
        double sampleMean = 0.0;
        for (std::size_t simulationIndex = 0; 
            simulationIndex < numberOfSimulations; ++simulationIndex) {
            process(0) = samples(simulationIndex);
            _discretizationScheme->simulateOneStep(process, 
                _model, time, timeStepSize, random);
            samples(simulationIndex) = process(0);

            sampleMean += samples(simulationIndex);
        }
        sampleMean /= numberOfSimulations;

        //do momemnt matiching
        for (std::size_t simulationIndex = 0; 
            simulationIndex < numberOfSimulations; ++simulationIndex) {
            samples(simulationIndex) = 
                _momentMatcher->doMomentMatch(
                    samples(simulationIndex), sampleMean, timeIndex);
            presentValues[simulationIndex] += 
                _presentValueCalculator->operator()(
                    samples(simulationIndex), simulationIndex, timeIndex);
        }
    }

    //calculate sample mean of PV.
    double sampleMean = 0.0;
    for (std::size_t simulationIndex = 0; 
        simulationIndex < numberOfSimulations; ++simulationIndex) {
        sampleMean += presentValues[simulationIndex];
    }
    sampleMean /= numberOfSimulations;
    const double price = sampleMean;

    return price;
}


