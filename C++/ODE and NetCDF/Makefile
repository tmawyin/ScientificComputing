# Makefile for ODE solver
#
# HW 2 of 'Numerical Tools for Physical Scientists'. 
#
# Tomas Mawyin - 996400531
#

# SETUP
CXX = g++
CXXFLAGS = -O2 -Wall
GSLINC = -I ${GSLINCDIR}
GSLLIB = -L ${GSLLIBDIR}
GSLFLG = -lgsl -lgslcblas -lm
NCDFLIB = -I ${NETCDFLIB}
NCDFFLG = -lnetcdf_c++4


all: solveODE
	./solveODE

solveODE: mainSolver.o odeSolver.o ioFile.o
	${CXX} ${CXXFLAGS} mainSolver.o odeSolver.o ioFile.o -o solveODE ${GSLLIB} ${GSLFLG} ${NCDFFLG}

mainSolver.o: Solver.cc
	${CXX} ${CXXFLAGS} ${NCDFLIB} Solver.cc -c -o mainSolver.o 

odeSolver.o: odeSolver.cc odeSolver.h
	${CXX} ${CXXFLAGS} ${GSLINC} odeSolver.cc -c -o odeSolver.o

ioFile.o: ioFile.cc ioFile.h 
	${CXX} ${CXXFLAGS} ioFile.cc -c -o ioFile.o

clean:
	rm -f odeSolver.o mainSolver.o ioFile.o resultMatrix.nc
