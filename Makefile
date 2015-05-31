#Suffix Rule
.SUFFIXES :
.SUFFIXES : .o .cpp
.cpp.o :
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $<

SELF = basic.mk

CC = g++
#DEBUG = -O2 -Wall
DEBUG = -Wall
CFLAGS = $(DEBUG)
INC_FLAGS = -I./

SDE_WA_SRC =  $(wildcard *.cpp)
SDE_WA_OBJS =  $(SDE_WA_SRC:.cpp=.o)
TARGETS = european_option 

.PHONY: all
all: $(TARGETS)

$(TARGETS): $(SDE_WA_OBJS)
	$(CC) $(SDE_WA_OBJS) -o $@

Makefile : $(SELF)
	rm -f $@
	cp $(SELF) $@
	chmod +w $@
	echo '# Automatically-generated dependencies list:' >>$@
	$(CC) ${CFLAGS} ${INC_FLAGS} -MM	\
	${SDE_WA_SRC}	\
	>> $@
	chmod -w $@

.PHONY: clean
clean :
	rm -f *.o $(TARGETS)

# Automatically-generated dependencies list:
BlackScholesDiffusion.o: BlackScholesDiffusion.cpp \
  BlackScholesDiffusion.h Diffusion.h
BlackScholesDrift.o: BlackScholesDrift.cpp BlackScholesDrift.h Drift.h
BlackScholesFactory.o: BlackScholesFactory.cpp BlackScholesFactory.h \
  StochasticDifferentialEquationFactory.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h \
  BlackScholesDrift.h BlackScholesDiffusion.h
CashFlow.o: CashFlow.cpp CashFlow.h
CashFlowAverage.o: CashFlowAverage.cpp CashFlowAverage.h
CashFlowCalculator.o: CashFlowCalculator.cpp CashFlowCalculator.h
CashFlowCall.o: CashFlowCall.cpp CashFlowCall.h CashFlow.h
CashFlowPut.o: CashFlowPut.cpp CashFlowPut.h CashFlow.h
CashFlowSpot.o: CashFlowSpot.cpp CashFlowSpot.h CashFlow.h
CashFlowSwap.o: CashFlowSwap.cpp CashFlowSwap.h
CashFlowSwaption.o: CashFlowSwaption.cpp CashFlowSwaption.h CashFlow.h \
  CashFlowSwap.h
Diffusion.o: Diffusion.cpp Diffusion.h
DiscretizationScheme.o: DiscretizationScheme.cpp DiscretizationScheme.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h
Drift.o: Drift.cpp
EulerMaruyama.o: EulerMaruyama.cpp EulerMaruyama.h DiscretizationScheme.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h
LiborMarketModelDiffusion.o: LiborMarketModelDiffusion.cpp \
  LiborMarketModelDiffusion.h Diffusion.h
LiborMarketModelDrift.o: LiborMarketModelDrift.cpp \
  LiborMarketModelDrift.h Drift.h
LiborMarketModelFactory.o: LiborMarketModelFactory.cpp \
  LiborMarketModelFactory.h StochasticDifferentialEquationFactory.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h \
  LiborMarketModelDrift.h LiborMarketModelDiffusion.h
LogPathSimulator.o: LogPathSimulator.cpp LogPathSimulator.h \
  PathSimulatorDecorator.h PathSimulatorBase.h
MersenneTwister.o: MersenneTwister.cpp MersenneTwister.h \
  RandomGeneratorBase.h
MonteCarloPricer.o: MonteCarloPricer.cpp MonteCarloPricer.h \
  PathSimulatorBase.h PresentValueCalculator.h
PathSimulator.o: PathSimulator.cpp PathSimulator.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h \
  DiscretizationScheme.h RandomGeneratorBase.h PathSimulatorBase.h
PathSimulatorBase.o: PathSimulatorBase.cpp PathSimulatorBase.h
PathSimulatorDecorator.o: PathSimulatorDecorator.cpp \
  PathSimulatorDecorator.h PathSimulatorBase.h
PayOff.o: PayOff.cpp PayOff.h
PayOffCaplet.o: PayOffCaplet.cpp PayOffCaplet.h PayOff.h
PayOffSwaption.o: PayOffSwaption.cpp PayOffSwaption.h PayOff.h
PlainVanillaPayOff.o: PlainVanillaPayOff.cpp PlainVanillaPayOff.h \
  PayOff.h
PresentValueCalculator.o: PresentValueCalculator.cpp \
  PresentValueCalculator.h
RandomGeneratorBase.o: RandomGeneratorBase.cpp RandomGeneratorBase.h
SabrDiffusion.o: SabrDiffusion.cpp SabrDiffusion.h Diffusion.h
SabrDrift.o: SabrDrift.cpp SabrDrift.h Drift.h
SabrFactory.o: SabrFactory.cpp SabrFactory.h \
  StochasticDifferentialEquationFactory.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h SabrDrift.h \
  SabrDiffusion.h
StochasticDifferentialEquation.o: StochasticDifferentialEquation.cpp \
  StochasticDifferentialEquation.h Drift.h Diffusion.h
StochasticDifferentialEquationFactory.o:  \
 StochasticDifferentialEquationFactory.cpp \
  StochasticDifferentialEquationFactory.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h
