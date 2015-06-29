// Contains function definitions to read and write netCDF files

#include "ioFile.h"

// Function to read netCDF file and print to screen
void readNetCDF()
{
	NcFile dataFile("resultMatrix.nc", NcFile::read);
	NcDim xDim = dataFile.getDim("rows");
	NcDim yDim = dataFile.getDim("columns");

	// Getting dimensions of the matrix
	int nx = xDim.getSize();
	int ny = yDim.getSize();
	
	// Setting pointers to store values
	double **p = new double *[nx];
	p[0] = new double[nx * ny];

	for(int i = 0; i < nx; i++)
		p[i] = &p[0][i * ny];
	
	// Put the data in a variable.
	NcVar data = dataFile.getVar("ResultMatrix");
	data.getVar(p[0]);

	// Printing file to standard output
	for(int i = 0; i < nx; i=i+10) 
	{
	std::cout << i*0.001 << " ";
		for(int j = 0; j < ny; j++)
		{
			std::cout << p[i][j] << " ";
		}
	std::cout << "\n";
	}
}

// Function writes netCDF file based on a dimension and values given. Stores a 2D array
void writeNetCDF(int dim, double values[][4])
{
	// Opening the NetCDF file
	NcFile dataFile("resultMatrix.nc", NcFile::replace);
	dataFile.putAtt("Creation date:","Feb 17,2015");
	dataFile.putAtt("Comment:","Created as part of SCMP132 Homework 6");
	dataFile.putAtt("Contains:","Vector solutions of ODE system");
	
	// Setting up the dimensions for all variables
	NcDim xDim = dataFile.addDim("rows",dim);
	NcDim yDim = dataFile.addDim("columns",4);
		
	std::vector<NcDim> dims;
	dims.push_back(xDim);
	dims.push_back(yDim);

	// Create the variable to store information
	NcVar data = dataFile.addVar("ResultMatrix", ncDouble, dims);
	data.putVar(values);
}
