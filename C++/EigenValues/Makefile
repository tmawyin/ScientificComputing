# Makefile for Eigenvalue solver
#
# HW 3 of 'Numerical Tools for Physical Scientists'. 
#
# Tomas Mawyin - 996400531
#

# SETUP
CXX = g++
CXXFLAGS = -O2 -Wall
BLASINC = -I ${BLAS_INC}
BLASLIB = -L ${BLAS_LIB}
BLASFLAG = -lopenblas

all: eigenSolver
	./eigenSolver

eigenSolver: eigenVal.cc eigenIO.o
	${CXX} ${CXXFLAGS} eigenVal.cc eigenIO.o -o eigenSolver ${BLASINC} ${BLASLIB} ${BLASFLAG}

eigenIO.o: eigenIO.cc
	${CXX} ${CXXFLAGS} eigenIO.cc -c -o eigenIO.o ${BLASINC} 

clean:
	rm -f eigenIO.o
