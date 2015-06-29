// Contains equation prototyping for ioFile.cc

#ifndef IOFILE_H
#define IOFILE_H

#include <netcdf>
#include <vector>
#include <iostream>
using namespace netCDF;

//Function to read netCDF file and print values to standard output
void readNetCDF();

// Function to write netCDF file based on values
void writeNetCDF(int dim, double values[][4]);

#endif
