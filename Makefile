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
  PathSimulatorBase.h PathDependent.h PayOff.h
PathDependent.o: PathDependent.cpp PathDependent.h
PathDependentAsian.o: PathDependentAsian.cpp PathDependentAsian.h \
  PathDependent.h PayOff.h
PathDependentEuropean.o: PathDependentEuropean.cpp \
  PathDependentEuropean.h PathDependent.h PayOff.h
PathSimulator.o: PathSimulator.cpp PathSimulator.h \
  StochasticDifferentialEquation.h Drift.h Diffusion.h \
  DiscretizationScheme.h RandomGeneratorBase.h PathSimulatorBase.h
PathSimulatorBase.o: PathSimulatorBase.cpp PathSimulatorBase.h
PathSimulatorDecorator.o: PathSimulatorDecorator.cpp \
  PathSimulatorDecorator.h PathSimulatorBase.h
PayOff.o: PayOff.cpp PayOff.h
PlainVanillaPayOff.o: PlainVanillaPayOff.cpp PlainVanillaPayOff.h \
  PayOff.h
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
main.o: main.cpp StochasticDifferentialEquation.h Drift.h Diffusion.h \
  BlackScholesFactory.h StochasticDifferentialEquationFactory.h \
  SabrFactory.h LiborMarketModelFactory.h EulerMaruyama.h \
  DiscretizationScheme.h MersenneTwister.h RandomGeneratorBase.h \
  PlainVanillaPayOff.h PayOff.h MonteCarloPricer.h PathSimulatorBase.h \
  PathDependent.h PathSimulator.h PathDependentEuropean.h
