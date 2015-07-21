void cloewlowChapter4Test()
{
/**************************************************************************
     * Programs on Chapter 4 in Clewlow.
     **************************************************************************/
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model. FIgure4.2.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = log(100.0);
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const LogBlackScholesFactory logBlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> logBlackScholes = 
            logBlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> blackScholesPathSimulator(
            new PathSimulator(logBlackScholes, eulerMaruyama, mersenneTwister));
        const boost::shared_ptr<const PathSimulatorBase> 
            logBlackScholesPathSimulator(
                new PathSimulatorExp(blackScholesPathSimulator));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectatorBase> expectation(
            new Expectator(presentValueCalculator));

        //create a pricer.
        const MonteCarloPricer pricer(logBlackScholesPathSimulator, 
            presentValueCalculator, expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.2:" << price << std::endl;
    }

    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with Antithetic Variance Reductin. FIgure4.5.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = log(100.0);
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const LogBlackScholesFactory logBlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> logBlackScholes = 
            logBlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> blackScholesPathSimulator(
            new PathSimulator(logBlackScholes, eulerMaruyama, antitheticMersenneTwister));
        const boost::shared_ptr<const PathSimulatorBase> logBlackScholesPathSimulator(
            new PathSimulatorExp(blackScholesPathSimulator));

        //cash flow
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //expectation
        const boost::shared_ptr<ExpectatorBase> expectation(
            new Expectator(presentValueCalculator));

        //create a pricer.
        const MonteCarloPricer pricer(logBlackScholesPathSimulator, 
            presentValueCalculator, expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.5:" << price << std::endl;
    }
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with a Delta-based Control Variate. FIgure4.9.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const BlackScholesFactory BlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
            BlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //observed Times
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> 
            blackScholesPathSimulator(
                new PathSimulator(blackScholes, eulerMaruyama, mersenneTwister));

        //cash flow
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));
        const boost::shared_ptr<const CashFlow>
            deltaHedge(new CashFlowDeltaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes, 
                europeanCall->getCashFlowDateIndex()));

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //control variates
        std::vector< boost::shared_ptr<const PresentValueCalculator> >
            controlVariates(1);
        boost::shared_ptr<const PresentValueCalculator>
            deltaControlVariate(
                new PresentValueCalculator(deltaHedge, discountFactors));
        controlVariates[0] = deltaControlVariate;

        //expectation
        const boost::shared_ptr<ExpectatorBase> expectation(
            new ExpectatorControlVariate(presentValueCalculator, 
                controlVariates));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            presentValueCalculator,
            expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.9:" << price << std::endl;
    }
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with a Delta-based Control Variate and Antithetic. FIgure4.11.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const BlackScholesFactory BlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
            BlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //observed Times
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> 
            blackScholesPathSimulator(
                new PathSimulator(blackScholes, eulerMaruyama, 
                antitheticMersenneTwister));

        //cash flow
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));
        const boost::shared_ptr<const CashFlow>
            deltaHedge(new CashFlowDeltaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes,
                europeanCall->getCashFlowDateIndex()));

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //control variates
        std::vector< boost::shared_ptr<const PresentValueCalculator> >
            controlVariates(1);
        boost::shared_ptr<const PresentValueCalculator>
            deltaControlVariate(
                new PresentValueCalculator(deltaHedge, discountFactors));
        controlVariates[0] = deltaControlVariate;

        //expectation
        const boost::shared_ptr<ExpectatorBase> expectation(
            new ExpectatorControlVariate(presentValueCalculator, 
                controlVariates));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            presentValueCalculator,
            expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.11:" << price << std::endl;
    }
    {
        /**********************************************************************
         * European Call Option under the BlackScholes Model
         * with a Delta-based Control Variate,
         * Gamma-based Control Variate and Antithetic. FIgure4.13.
         **********************************************************************/
        const double strike = 100.0;
        const double maturity = 1.0;
        boost::numeric::ublas::vector<double> spots(1);
        spots[0] = 100.0;
        const double volatility = 0.2;
        const double interestRate = 0.06;
        const double dividend = 0.03;
        const double numberOfTimeSteps = 10;
        const double numberOfSimulations = 100;

        //Logarithmic BlackScholes Model by Factory patter.
        const BlackScholesFactory BlackScholesFactory(
            interestRate, dividend, volatility);
        boost::shared_ptr<const StochasticDifferentialEquation> blackScholes = 
            BlackScholesFactory.makeStochasticDifferentialEquation();

        //discretization scheme.
        boost::shared_ptr<EulerMaruyama> eulerMaruyama(new EulerMaruyama());

        //random number generator.
        boost::shared_ptr<MersenneTwister> mersenneTwister(
            new MersenneTwister(numberOfTimeSteps, 0));
        boost::shared_ptr<AntitheticRandom> antitheticMersenneTwister(
            new AntitheticRandom(mersenneTwister));

        //observed Times
        const std::vector<double> observedTimes =
            makeObservedTimes(maturity, numberOfTimeSteps);

        //discount factors
        const boost::numeric::ublas::vector<double> discountFactors =
            makeDiscountFactors(interestRate, observedTimes);

        //path simulator.
        const boost::shared_ptr<const PathSimulatorBase> 
            blackScholesPathSimulator(
                new PathSimulator(blackScholes, eulerMaruyama, 
                antitheticMersenneTwister));

        //cash flow
        const boost::shared_ptr<const CashFlow> 
            cashFlowSpot(new CashFlowSpot(
                observedTimes.size() - 1, observedTimes.size() - 1, 0));
        const boost::shared_ptr<const CashFlow>
            europeanCall(new CashFlowCall(strike, cashFlowSpot));
        const boost::shared_ptr<const CashFlow>
            deltaHedge(new CashFlowDeltaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes,
                europeanCall->getCashFlowDateIndex()));
        const boost::shared_ptr<const CashFlow>
            gammaHedge(new CashFlowGammaHedge(
                strike, maturity, volatility, interestRate, dividend,
                discountFactors, observedTimes, 
                europeanCall->getCashFlowDateIndex()));

        //present value calculator.
        const boost::shared_ptr<const PresentValueCalculator> 
            presentValueCalculator(
                new PresentValueCalculator(europeanCall, discountFactors));

        //control variates
        std::vector< boost::shared_ptr<const PresentValueCalculator> >
            controlVariates(2);
        boost::shared_ptr<const PresentValueCalculator>
            deltaControlVariate(
                new PresentValueCalculator(deltaHedge, discountFactors));
        boost::shared_ptr<const PresentValueCalculator>
            gammaControlVariate(
                new PresentValueCalculator(gammaHedge, discountFactors));
        controlVariates[0] = deltaControlVariate;
        controlVariates[1] = gammaControlVariate;

        //expectation
        const boost::shared_ptr<ExpectatorBase> expectation(
            new ExpectatorControlVariate(presentValueCalculator, 
                controlVariates));

        //create a pricer.
        const MonteCarloPricer pricer(blackScholesPathSimulator, 
            presentValueCalculator,
            expectation);

        const double price = pricer.simulatePrice(
            spots, numberOfSimulations, observedTimes, discountFactors);
        std::cout << "Figure4.13:" << price << std::endl;
    }
}

