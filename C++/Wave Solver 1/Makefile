# Makefile 
# SCMP122 - Homework 2
# Tomas Mawyin

CPP = g++
CPPFLAGS = -Wall -O2

all: waveSolver

waveSolver: waveDriver.cpp waveRead.o waveStep.o
	${CPP} waveDriver.cpp waveRead.o waveStep.o \
	-o waveSolver ${CPPFLAGS}

waveRead.o: waveRead.cpp
	${CPP} waveRead.cpp -c -o waveRead.o ${CPPFLAGS}

waveStep.o: waveStep.cpp
	${CPP} waveStep.cpp -c -o waveStep.o ${CPPFLAGS}

clean:
	rm -f waveStep.o waveRead.o 

