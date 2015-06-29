# Makefile for root finder
# implemented in solverRoot.cc
#
# HW 1 of 'Numerical Tools for Physical Scientists'. 
#
# Tomas Mawyin - 996400531
#

# SETUP
CXX = g++
CXXFLAGS = -O2 -Wall
GSLINC = -I ${GSLINCDIR}
GSLLIB = -L ${GSLLIBDIR}
BOOSTLIB = -I ${BOOST_ROOT}
GSLFLG = -lgsl -lgslcblas -lm

all: RootSolver
	./RootSolver

test: solverTest
	./solverTest

solverTest: solverTest.cc solverRoot.cc
	${CXX} ${BOOSTLIB} ${GSLINC} ${GSLLIB}  solverTest.cc solverRoot.cc -o solverTest ${GSLFLG}

RootSolver: solverMain.o solverRoot.o
	${CXX} ${CXXFLAGS} solverMain.o solverRoot.o -o RootSolver ${GSLLIB} ${GSLFLG}

solverRoot.o: solverRoot.cc solverRoot.h
	${CXX} ${CXXFLAGS} solverRoot.cc -c -o solverRoot.o

solverMain.o: solverMain.cc
	${CXX} -c ${CXXFLAGS} ${GSLINC} solverMain.cc -o solverMain.o

clean:
	rm -f solverRoot.o solverMain.o

