// Contains equation prototyping for ioFile.cc

#ifndef IOFILE_H
#define IOFILE_H

#include <netcdf>
#include <vector>
#include <iostream>
#include <string>

using namespace netCDF;

// Converts single vector rho to a matrix to store all instances of the vector as time marches
void saveRho(int npnts, int timeCount, double** &rhoFull, double* rho);

//Function to read netCDF file and print values to standard output
void readNetCDF();

// Function to write netCDF file based on values
void writeNetCDF(int npnts, int tSize, double *t, double** rho, double* x);

#endif
