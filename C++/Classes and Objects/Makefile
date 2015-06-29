# Makefile 
# SCMP122 - Homework 3
# Tomas Mawyin

CPP = g++
CPPFLAGS = -Wall -O2

all: makethiswork

makethiswork: makethiswork.cc mymatrix.o
	${CPP} makethiswork.cc mymatrix.o -o makethiswork ${CPPFLAGS}

mymatrix.o: mymatrix.cc
	${CPP} mymatrix.cc -c -o mymatrix.o ${CPPFLAGS}

clean:
	rm -f *.o *.dat

