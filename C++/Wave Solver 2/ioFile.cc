// Contains function definitions to read and write netCDF files

#include "ioFile.h"

// Converts single vector rho to a matrix to store all instances of the vector as time marches
void saveRho(int npnts, int timeCount, double** &rhoFull, double* rho)
{
    for(int i=0; i < npnts; i++)
    {
        rhoFull[i][timeCount] = rho[i];
    }
}

// Function to read netCDF file and print to screen
void readNetCDF()
{
	NcFile dataFile("resultMatrix.nc", NcFile::read);
	NcDim xDim = dataFile.getDim("X");
	NcDim tDim = dataFile.getDim("T");
	NcDim rhoXDim = dataFile.getDim("rho_rows");
	NcDim rhoYDim = dataFile.getDim("rho_cols");

	// Getting dimensions of the matrix
	int nX = xDim.getSize();
	int nT = tDim.getSize();
	int xRho = rhoXDim.getSize();
	int yRho = rhoYDim.getSize();
	
	std::cout << "x dimension: " << nX << '\n';
	std::cout << "time points: " << nT << '\n';
	std::cout << "rho dimension: " << xRho << '\n';
	// Setting pointers to store values
	double* x = new double[nX];
	double* t = new double[nT];
	double **p = new double *[xRho];
	p[0] = new double[xRho * yRho];
	for(int i = 0; i < xRho; i++)
		p[i] = &p[0][i * yRho];
		
	// Put the data in a variable.
	NcVar xData = dataFile.getVar("x");
	xData.getVar(x);
	NcVar tData = dataFile.getVar("t");
	tData.getVar(t);
	NcVar rhoData = dataFile.getVar("rho");
	rhoData.getVar(p[0]);

	// Printing file to standard output
	for(int i = 0; i < nT; i++) 
	{
		std::cout <<"Time t = "<< t[i] <<'\n';
		for(int j=0; j< nX; j++)
		{
			std::cout << x[j] << "    " << p[j][i] << "\n";
		}

	}

	// Deallocation memory
    delete [] p[0];
    delete [] p;
}

// Function writes netCDF file based on a dimension and values given. Stores a 2D array
void writeNetCDF(int npnts, int tSize, double *t, double** rho, double* x)
{
		NcFile dataFile("resultMatrix.nc", NcFile::replace);
		// Adding attributes to the file
		dataFile.putAtt("Creation date:","Mar 7,2015");
		dataFile.putAtt("Comment:","Created as part of SCMP132 Homework 8");
		dataFile.putAtt("Contains:","Vectors of x and rho for each time t");
		
		// Create the variable to store information
		// Time
		NcDim tDim = dataFile.addDim("T",tSize);
		std::vector<NcDim> tdims;
		tdims.push_back(tDim);
		NcVar tData = dataFile.addVar("t", ncDouble, tdims);
		tData.putVar(t);
		// X
		NcDim xDim = dataFile.addDim("X",npnts);
		std::vector<NcDim> xdims;
		xdims.push_back(xDim);
		NcVar xData = dataFile.addVar("x", ncDouble, xdims);
		xData.putVar(x);
		// Rho
		NcDim rhoXDim = dataFile.addDim("rho_rows",npnts);
		NcDim rhoYDim = dataFile.addDim("rho_cols",tSize);
		std::vector<NcDim> rhodims;
		rhodims.push_back(rhoXDim);
		rhodims.push_back(rhoYDim);
		NcVar rhoData = dataFile.addVar("rho", ncDouble, rhodims);
		rhoData.putVar(rho[0]);
}
