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
#include "Function1DStepWise.h"
#include "Function2DLogInterpolate.h"
#include "LocalVolatilityFactory.h"
#include "LogEulerMaruyama.h"
#include "CashFlowTargetRedemptionForward.h"
#include "SampleTransformExp.h"
#include "SampleTransformNull.h"
#include "PredictorCorrector.h"
#include "CashFlowMomentMatching.h"
#include "CashFlowTargetRedemptionForwardMomentMatching.h"
#include "MomentMatcherFirst.h"
#include "PresentValueCalculatorMomentMatching.h"
#include "SampleTransformInverse.h"
#include "Solver.h"
#include "NewtonRaphson.h"
#include "MonteCarloMomentMatchingPricer.h"

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/math/distributions/normal.hpp>


struct Integrand {
    Integrand(Function2DLogInterpolate& function) : _function(function){};
    ~Integrand(){};

    double operator()(
        const double time,
        const double state) {
        return 1.0 / _function(time, state);
    }

    Function2DLogInterpolate _function;
};

Function1DStepWise makeDriftFunction(const std::vector<double>& timeGrid)
{
    const double interestRate = 0.01;
    boost::numeric::ublas::vector<double> steps(timeGrid.size() + 1, interestRate);

    std::vector<std::size_t> timeGridIndex(timeGrid.size());
    for (std::size_t timeIndex = 0; timeIndex < timeGridIndex.size(); 
        ++timeIndex) {
        timeGridIndex[timeIndex] = timeIndex;
    }
    TimeIndexManager timeIndexManager(timeGrid, timeGridIndex);

    return Function1DStepWise(steps, timeIndexManager);
}

Function2DLogInterpolate makeDiffusionFunction()
{
    namespace ublas = boost::numeric::ublas;
    //make volatility and strikes
    ublas::matrix<double> strikes(8, 7); 
    ublas::matrix<double> volatilities(8, 7); 
    const double volatility[] = {0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23, 0.24};
    for (int strikeIndex = 0; strikeIndex < 7; ++strikeIndex) {
        strikes(0, strikeIndex) = 100.0 + 5 * (strikeIndex - 3);
        strikes(1, strikeIndex) = 95.0 + 5 * (strikeIndex - 3);
        strikes(2, strikeIndex) = 90.0 + 5 * (strikeIndex - 3);
        strikes(3, strikeIndex) = 85.0 + 5 * (strikeIndex - 3);
        strikes(4, strikeIndex) = 90.0 + 5 * (strikeIndex - 3);
        strikes(5, strikeIndex) = 95.0 + 5 * (strikeIndex - 3);
        strikes(6, strikeIndex) = 100.0 + 5 * (strikeIndex - 3);
        strikes(7, strikeIndex) = 100.0 + 5 * (strikeIndex - 3);
        volatilities(0, strikeIndex) = volatility[0] + 0.02 * (strikeIndex - 3);
        volatilities(1, strikeIndex) = volatility[1] + 0.02 * (strikeIndex - 3);
        volatilities(2, strikeIndex) = volatility[2] + 0.02 * (strikeIndex - 3);
        volatilities(3, strikeIndex) = volatility[3] + 0.02 * (strikeIndex - 3);
        volatilities(4, strikeIndex) = volatility[4] + 0.02 * (strikeIndex - 3);
        volatilities(5, strikeIndex) = volatility[5] + 0.02 * (strikeIndex - 3);
        volatilities(6, strikeIndex) = volatility[6] + 0.02 * (strikeIndex - 3);
        volatilities(7, strikeIndex) = volatility[7] + 0.02 * (strikeIndex - 3);
    }

    //make time index manager
    std::vector<double> timeGrid(8);
    std::vector<std::size_t> timeGridIndex(8);
    double times[8] = {7.0/360.0, 14.0/360.0, 
        30.0/360.0, 60.0/360.0, 90.0/360.0,
        180.0/360.0, 270.0/360.0, 360.0/360.0};
    for (std::size_t timeIndex = 0; timeIndex < timeGridIndex.size(); ++timeIndex) {
        timeGrid[timeIndex] = times[timeIndex];
        timeGridIndex[timeIndex] = timeIndex;
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
        discountFactors[timeIndex] = 
            exp(-interestRate * (timeGrid[timeIndex] - timeGrid[0]));
        discountFactors[timeIndex] = 1.0;
    }
    
    return discountFactors;
}

boost::numeric::ublas::vector<double> makeForwardPrice(
    const Function1DStepWise& mu,
    const std::vector<double>& timeGrid)
{
    boost::numeric::ublas::vector<double> forwardPrice(timeGrid.size());
    
    for (std::size_t gridIndex = 0; gridIndex < timeGrid.size(); ++gridIndex) {
        forwardPrice[gridIndex] = exp(mu.integral(0.0, timeGrid[gridIndex]));
    }
    return forwardPrice;
}

Function2DLogInterpolate* g_diffusion;
Function2DLogInterpolate* hogehoge;

/******************************************************************************
 * Target Redemption Forward simulation.
 ******************************************************************************/
void calculateTargetRedemptionForward()
{
    /**************************************************************************
     * Parameter settings.
     **************************************************************************/
    const double strike = 100.0;
    const double targetLevel = 30000.0;
    const double spot = log(100.0);
    //const double spot = 100.0;
    const double interestRate = 0.01;
    const boost::numeric::ublas::vector<double> spots(1, spot);

    
    const std::size_t numberOfTimeSteps = 36 * 6;
    const std::size_t numberOfSimulations = 100;

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
    Function2DLogInterpolate diffusion = makeDiffusionFunction();
    hogehoge = &diffusion;
    const LocalVolatilityFactory localVolatilityFactory(drift, diffusion, false);
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
            numberOfSimulations, timeGrid, diffusion);
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
    const std::size_t numberOfSimulations = 100;

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
    Function2DLogInterpolate diffusion = makeDiffusionFunction();
    g_diffusion = &diffusion;
    const LocalVolatilityFactory localVolatilityFactory(drift, diffusion, true);
    boost::shared_ptr<const StochasticDifferentialEquation> localVolatility = 
        localVolatilityFactory.makeStochasticDifferentialEquation();

    //transform
    boost::shared_ptr<SampleTransformInverse> transform(
        new SampleTransformInverse(diffusion, log(50.0), log(200.0), 100));

    //discretization scheme.
    boost::shared_ptr<PredictorCorrector> discretization(
        new PredictorCorrector(transform, 1, 0.5, 0.5));

    //random number generator.
    boost::shared_ptr<MersenneTwister> mersenneTwister(
        new MersenneTwister(numberOfSimulations, 0));
    //discount factors
    const std::vector<double> discountFactors =
        makeDiscountFactors(interestRate, timeGrid);
    //cash flow.
    const boost::shared_ptr<CashFlowCalculatorMomentMatching> 
        cashFlowTRF(new CashFlowTargetRedemptionForwardMomentMatching(
            numberOfSimulations, strike, targetLevel, excerciseDate));
    const boost::shared_ptr<CashFlowMomentMatching> cashFlow(
        new CashFlowMomentMatching(cashFlowTRF));

    //MomentMatcher
    boost::numeric::ublas::vector<double> forwardPrice = makeForwardPrice(
        drift, timeGrid);
    const boost::shared_ptr<MomentMatcherFirst> momentMatcher(
        new MomentMatcherFirst(forwardPrice));

    //present value calculator
    const boost::shared_ptr<PresentValueCalculatorMomentMatching> 
        presentValueCalculator(
            new PresentValueCalculatorMomentMatching(
                cashFlow, discountFactors, numberOfSimulations));

    
    //pricer
    boost::shared_ptr<const MonteCarloMomentMatchingPricer> pricer(
        new MonteCarloMomentMatchingPricer(
            localVolatility,
            discretization, 
            momentMatcher,
            presentValueCalculator,
            mersenneTwister));
    /**********************************************************************
     * Calculate Price.
     **********************************************************************/
    {
        const double price = pricer->simulatePrice(g_diffusion->integrateByState(0.0, spot), 
            numberOfSimulations, timeGrid);
        std::cout << "TRF Price:" << price << std::endl;
    }
    

    std::cout << std::endl;
}

int testFunction2DLogInterpolate()
{
    Function2DLogInterpolate vol = makeDiffusionFunction();
    double spot = 100.0;
    std::cout << vol(5.5, spot) << std::endl;

    std::cout << "differentialByState:" << vol.differentialByState(1.5, spot) << std::endl;

    return 0;
}

int testSolver()
{
    Solver solver;
    const double tolerance = 0.1;
    const double time = 1.0;
    Function2DLogInterpolate vol = makeDiffusionFunction();
    std::vector<double> zs(5);
    double xs[] = {log(90.0), log(95.0), log(100.0), log(105.0), log(110.0)};
    for (std::size_t index = 0; index < zs.size(); ++index) {
        zs[index] = vol.integrateByState(time, xs[index]);
        std::cout << xs[index] << "\t\t" << zs[index] << std::endl;
    }

    Integrand integrand(vol);

    //function
    boost::function<double(double)> function = 
        boost::bind(
            &Function2DLogInterpolate::integrateByState, &vol, time, _1);
    //differential of the funtcion
    boost::function<double(double)> differential = 
        boost::bind(&Integrand::operator(), 
            &integrand, time, _1);

    const boost::shared_ptr<NewtonRaphson> engine(
        new NewtonRaphson(function, differential));

    for (std::size_t index = 0; index < zs.size(); ++index) {
        const double x = solver.solve(2.0, zs[index], tolerance, engine);
        std::cout << x  << "\t" << zs[index] << std::endl;
    }

    return 0;
}

int testSampleTransFormInverse()
{
    Function2DLogInterpolate vol = makeDiffusionFunction();
    double from = log(80.0);
    double to = log(120.0);
    std::size_t numberOfPartitions = 10;

    std::cout << "start" << std::endl;
    const boost::shared_ptr<SampleTransformInverse> transform(
        new SampleTransformInverse(vol, from, to, numberOfPartitions));
    std::cout << "end" << std::endl;
    std::cout << transform->operator()(1.0, log(90.0)) << std::endl;

    return 0;
}

int main()
{
    //calculateTargetRedemptionForward();
    calculateTargetRedemptionForwardMomentMatching();

    //testFunction2DLogInterpolate();
    //testSolver();
    //testSampleTransFormInverse();
    {
        int a = 0;
        std::cin >> a;
    }

    return 0;

}


