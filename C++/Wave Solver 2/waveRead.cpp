// File contains all the function definitions for read/write operations

#include "waveRead.h"

// Function reads the file to set up the parameters. Initializes all required physical and simulation parameters
void readParameters(int argc, char* argv, double &c, double &tau, double &x1, double &x2, double &runtime, double &dx, double &outtime)
{
	// If more than 1 arguments are given (i.e. a file is given), read the file and assign values to corresponding variables
	if (argc >1)
	{
		// argv: contains the string with the name of the file
		std::ifstream infile(argv);
		infile >> c;
		infile >> tau;
		infile >> x1;
		infile >> x2;
		infile >> runtime;
		infile >> dx;
		infile >> outtime;
		infile.close();
	}else{
		c       =   1.0;  // wave speed
		tau     =  20.0;  // damping time
		x1      = -26.0;  // left most x value
		x2      = +26.0;  // right most x value
		runtime = 200.0;  // how long should the simulation try to compute?
		dx      = 0.02;   // spatial grid size
		outtime =  1.0;   // write every so often
	}
}


