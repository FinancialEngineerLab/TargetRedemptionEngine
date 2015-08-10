#include "StochasticDifferentialEquation.h"
#include "BlackScholesFactory.h"
#include "EulerMaruyama.h"
#include "MersenneTwister.h"
#include "AntitheticRandom.h"
#include "MonteCarloPricer.h"
#include "PathSimulator.h"
#include "PathSimulatorExp.h"
#include "CashFlowCall.h"
#include "Expectator.h"
#include "ExpectatorControlVariate.h"
#include "FunctionCaplet.h"
#include "Function1DStepWise.h"
#include "Function2DLogInterpolate.h"
#include "LocalVolatilityFactory.h"
#include "LogEulerMaruyama.h"
#include "CashFlowTargetRedemptionForward.h"
#include "SampleTransformExp.h"
#include "SampleTransformNull.h"

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/math/distributions/normal.hpp>


Function1DStepWise makeDriftFunction(const std::vector<double>& timeGrid)
{
    const double interestRate = 0.01;
    boost::numeric::ublas::vector<double> steps(36, interestRate);

    std::vector<std::size_t> timeGridIndex(36);
    for (std::size_t timeIndex = 0; timeIndex < timeGridIndex.size(); ++timeIndex) {
        timeGridIndex[timeIndex] = timeIndex;
    }
    TimeIndexManager timeIndexManager(timeGrid, timeGridIndex);

    return Function1DStepWise(steps, timeIndexManager);
}

Function2DLogInterpolate makeDiffusionFunction(
    const std::vector<double>& timeGrid)
{
    namespace ublas = boost::numeric::ublas;
    //make volatility and strikes
    ublas::matrix<double> strikes(8, 7); 
    ublas::matrix<double> volatilities(8, 7); 
    const double volatility = 0.2;
    for (int strikeIndex = 0; strikeIndex < 7; ++strikeIndex) {
        strikes(0, strikeIndex) = 100.0 + 5 * (strikeIndex - 3);
        strikes(1, strikeIndex) = 95.0 + 5 * (strikeIndex - 3);
        strikes(2, strikeIndex) = 90.0 + 5 * (strikeIndex - 3);
        strikes(3, strikeIndex) = 85.0 + 5 * (strikeIndex - 3);
        strikes(4, strikeIndex) = 90.0 + 5 * (strikeIndex - 3);
        strikes(5, strikeIndex) = 950.0 + 5 * (strikeIndex - 3);
        strikes(6, strikeIndex) = 100.0 + 5 * (strikeIndex - 3);
        strikes(7, strikeIndex) = 100.0 + 5 * (strikeIndex - 3);
        volatilities(0, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
        volatilities(1, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
        volatilities(2, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
        volatilities(3, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
        volatilities(4, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
        volatilities(5, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
        volatilities(6, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
        volatilities(7, strikeIndex) = volatility + 0.02 * (strikeIndex - 3);
    }

    //make time index manager
    std::vector<std::size_t> timeGridIndex(8);
    int times[8] = {7.0/360.0, 14.0/360.0, 
        30.0/360.0, 60.0/360.0, 90.0/360.0,
        180.0/360.0, 270.0/360.0, 360.0/360.0};
    for (std::size_t timeIndex = 0; timeIndex < timeGridIndex.size(); ++timeIndex) {
        timeGridIndex[timeIndex] = times[timeIndex];
    }
    TimeIndexManager timeIndexManager(timeGrid, timeGridIndex);

    return Function2DLogInterpolate(strikes, volatilities, timeIndexManager);
}

std::vector<double> makeDiscountFactors(
    const double interestRate, 
    const std::vector<double>& timeGrid)
{
    std::vector<double> discountFactors(timeGrid.size());

    for (std::size_t timeIndex = 0; timeIndex < timeGrid.size(); ++timeIndex) {
        discountFactors[timeIndex] = exp(-interestRate * (timeGrid[timeIndex] - timeGrid[0]));
        discountFactors[timeIndex] = 1.0;
    }
    
    return discountFactors;
}



/******************************************************************************
 * Target Redemption Forward simulation.
 ******************************************************************************/
void calculateTargetRedemptionForward()
{
    /**********************************************************************
     * Parameter settings.
     **********************************************************************/
    const double strike = 100.0;
    const double targetLevel = 30000.0;
    const double spot = log(100.0);
    //const double spot = 100.0;
    const double interestRate = 0.01;
    const boost::numeric::ublas::vector<double> spots(1, spot);

    
    const std::size_t numberOfTimeSteps = 36 * 6;
    const std::size_t numberOfSimulations = 100000;

    //make Indice
    std::vector<double> timeGrid(numberOfTimeSteps + 1);
    std::vector<std::size_t> timeGridIndex(numberOfTimeSteps + 1);
    for (std::size_t timeIndex = 0; timeIndex < timeGrid.size(); 
        ++timeIndex) {
        timeGrid[timeIndex] = timeIndex * (5.0 / 360.0);
        timeGridIndex[timeIndex] = timeIndex;
    }
    TimeIndexManager timeGridManager(timeGrid, timeGridIndex);

    //excerciseDate
    std::vector<std::size_t> excerciseDateIndex(36);
    for (std::size_t timeIndex = 0; timeIndex < timeGrid.size(); 
        ++timeIndex) {
        excerciseDateIndex[timeIndex] = (timeIndex + 1) * 6;
    }
    TimeIndexManager excerciseDate(timeGrid, excerciseDateIndex);

    //Local Volatility Model creation
    Function1DStepWise drift = makeDriftFunction(timeGrid);
    Function2DLogInterpolate diffusion = makeDiffusionFunction(timeGrid);
    const LocalVolatilityFactory localVolatilityFactory(drift, diffusion);
    boost::shared_ptr<const StochasticDifferentialEquation> localVolatility = 
        localVolatilityFactory.makeStochasticDifferentialEquation();

    //discretization scheme.
    boost::shared_ptr<LogEulerMaruyama> discretization(new LogEulerMaruyama(1));
    const boost::shared_ptr<SampleTransform> transform(new SampleTransformExp());
    //boost::shared_ptr<EulerMaruyama> discretization(new EulerMaruyama(1));
    //const boost::shared_ptr<SampleTransform> transform(new SampleTransformNull());

    //random number generator.
    boost::shared_ptr<MersenneTwister> mersenneTwister(
        new MersenneTwister(numberOfTimeSteps, 0));
    //path simulator
    const boost::shared_ptr<const PathSimulatorBase> pathSimulator(
        new PathSimulator(localVolatility, discretization));

    //discount factors
    const std::vector<double> discountFactors =
        makeDiscountFactors(interestRate, timeGrid);

    //cash flow.
    const boost::shared_ptr<const CashFlowCalculator> cashFlowTRF(
        new CashFlowTargetRedemptionForward(strike, targetLevel, 
            discountFactors, excerciseDate, transform));
    const boost::shared_ptr<const CashFlow> cashFlow(
        new CashFlow(cashFlowTRF, 0));

    //present value calculator
    const boost::shared_ptr<const PresentValueCalculator> 
        presentValueCalculator(
            new PresentValueCalculator(cashFlow, discountFactors));

    //expectation
    const boost::shared_ptr<ExpectatorBase> expectation(
        new Expectator(presentValueCalculator));

    //pricer
    boost::shared_ptr<const MonteCarloPricer> pricer(
        new MonteCarloPricer(pathSimulator, 
            expectation, mersenneTwister));

    /**********************************************************************
     * Calculate Price.
     **********************************************************************/
    {
        const double price = pricer->simulatePrice(spots, 
            numberOfSimulations, timeGrid);
        std::cout << "TRF Price:" << price << std::endl;
    }
    

    std::cout << std::endl;
}

/******************************************************************************
 * Target Redemption Forward simulation.
 ******************************************************************************/
void calculateTargetRedemptionForwardMomentMatching()
{
    /**********************************************************************
     * Parameter settings.
     **********************************************************************/
    const double strike = 100.0;
    const double targetLevel = 30000.0;
    const double spot = log(100.0);
    //const double spot = 100.0;
    const double interestRate = 0.01;
    const boost::numeric::ublas::vector<double> spots(1, spot);

    
    const std::size_t numberOfTimeSteps = 36 * 6;
    const std::size_t numberOfSimulations = 100000;

    //make Indice
    std::vector<double> timeGrid(numberOfTimeSteps + 1);
    std::vector<std::size_t> timeGridIndex(numberOfTimeSteps + 1);
    for (std::size_t timeIndex = 0; timeIndex < timeGrid.size(); 
        ++timeIndex) {
        timeGrid[timeIndex] = timeIndex * (5.0 / 360.0);
        timeGridIndex[timeIndex] = timeIndex;
    }
    TimeIndexManager timeGridManager(timeGrid, timeGridIndex);

    //excerciseDate
    std::vector<std::size_t> excerciseDateIndex(36);
    for (std::size_t timeIndex = 0; timeIndex < timeGrid.size(); 
        ++timeIndex) {
        excerciseDateIndex[timeIndex] = (timeIndex + 1) * 6;
    }
    TimeIndexManager excerciseDate(timeGrid, excerciseDateIndex);

    //Local Volatility Model creation
    Function1DStepWise drift = makeDriftFunction(timeGrid);
    Function2DLogInterpolate diffusion = makeDiffusionFunction(timeGrid);
    const LocalVolatilityFactory localVolatilityFactory(drift, diffusion);
    boost::shared_ptr<const StochasticDifferentialEquation> localVolatility = 
        localVolatilityFactory.makeStochasticDifferentialEquation();

    //discretization scheme.
    boost::shared_ptr<LogEulerMaruyama> discretization(new LogEulerMaruyama(1));
    const boost::shared_ptr<SampleTransform> transform(new SampleTransformExp());
    //boost::shared_ptr<EulerMaruyama> discretization(new EulerMaruyama(1));
    //const boost::shared_ptr<SampleTransform> transform(new SampleTransformNull());

    //random number generator.
    boost::shared_ptr<MersenneTwister> mersenneTwister(
        new MersenneTwister(numberOfTimeSteps, 0));
    //path simulator
    const boost::shared_ptr<const PathSimulatorBase> pathSimulator(
        new PathSimulator(localVolatility, discretization));

    //discount factors
    const std::vector<double> discountFactors =
        makeDiscountFactors(interestRate, timeGrid);

    //cash flow.
    const boost::shared_ptr<const CashFlowCalculator> cashFlowTRF(
        new CashFlowTargetRedemptionForward(strike, targetLevel, 
            discountFactors, excerciseDate, transform));
    const boost::shared_ptr<const CashFlow> cashFlow(
        new CashFlow(cashFlowTRF, 0));

    //present value calculator
    const boost::shared_ptr<const PresentValueCalculator> 
        presentValueCalculator(
            new PresentValueCalculator(cashFlow, discountFactors));

    //expectation
    const boost::shared_ptr<ExpectatorBase> expectation(
        new Expectator(presentValueCalculator));

    //pricer
    boost::shared_ptr<const MonteCarloPricer> pricer(
        new MonteCarloPricer(pathSimulator, 
            expectation, mersenneTwister));

    /**********************************************************************
     * Calculate Price.
     **********************************************************************/
    {
        const double price = pricer->simulatePrice(spots, 
            numberOfSimulations, timeGrid);
        std::cout << "TRF Price:" << price << std::endl;
    }
    

    std::cout << std::endl;
}


int main()
{
    calculateTargetRedemptionForward();

    {
        int a = 0;
        std::cin >> a;
    }

    return 0;

}


