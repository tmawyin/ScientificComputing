# Makefile 
# SCMP132 - Homework 4
# Modification of Driver function from HW2
#
# Tomas Mawyin - 996400531

CPP = g++
CPPFLAGS = -Wall -O2
BLASINC = -I ${BLAS_INC}
BLASLIB = -L ${BLAS_LIB}
BLASFLAG = -lopenblas
NCDFLIB = -I ${NETCDFLIB}
NCDFFLG = -lnetcdf_c++4


banded: waveDriver.cpp waveRead.o waveStep.o evolveBand.o ticktock.o ioFile.o
	${CPP} waveDriver.cpp waveRead.o waveStep.o evolveBand.o ticktock.o ioFile.o -o waveSolver ${CPPFLAGS} ${BLASINC} ${BLASLIB} ${BLASFLAG} ${NCDFLIB} ${NCDFFLG}

full: waveDriver.cpp waveRead.o waveStep.o evolveFull.o ticktock.o ioFile.o
	${CPP} waveDriver.cpp waveRead.o waveStep.o evolveFull.o ticktock.o ioFile.o -o waveSolver ${CPPFLAGS} ${BLASINC} ${BLASLIB} ${BLASFLAG} ${NCDFLIB} ${NCDFFLG}

# Time marching using the full matrix operator
evolveFull.o: evolveFull.cc
	${CPP} evolveFull.cc -c -o evolveFull.o ${CPPFLAGS} ${BLASINC} ${BLASLIB} ${BLASFLAG}

# Time marching using the banded matrix operator
evolveBand.o: evolveBanded.cc
	${CPP} evolveBanded.cc -c -o evolveBand.o ${CPPFLAGS} ${BLASINC} ${BLASLIB} ${BLASFLAG}

# Provides link to the files in charge of reading and writing data in text format 
waveRead.o: waveRead.cpp
	${CPP} waveRead.cpp -c -o waveRead.o ${CPPFLAGS}

# Provides link to the files that initialize, and move the wave
waveStep.o: waveStep.cpp
	${CPP} waveStep.cpp -c -o waveStep.o ${CPPFLAGS}

ticktock.o: ticktock.cc ticktock.h
	${CPP} ${CPPFLAGS} -c -o ticktock.o ticktock.cc

ioFile.o: ioFile.cc ioFile.h 
	${CPP} ${CPPFLAGS} ioFile.cc -c -o ioFile.o

clean:
	rm -f waveStep.o waveRead.o evolveBand.o evolveFull.o ticktock.o ioFile.o outputFile.txt

