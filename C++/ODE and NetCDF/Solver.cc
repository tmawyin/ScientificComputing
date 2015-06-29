// SCMP132 - HW6: Solving ODEs using GSL library
// by Tomas Mawyin
//
// This file contains the main function for the ODE solver
// Solving a point particle bouncing on a soft but uneven floor

#include "odeSolver.h"
#include "ioFile.h"

int main (void)
{
	// Sets up the step type to use
	const gsl_odeiv2_step_type * T = gsl_odeiv2_step_rk4;
	// Allocates the stepping function
	gsl_odeiv2_step * s = gsl_odeiv2_step_alloc (T, 4);
	// Controls local error
	gsl_odeiv2_control * c = gsl_odeiv2_control_y_new (1e-6, 0.0);
	// Controls the evolution function
	gsl_odeiv2_evolve * e = gsl_odeiv2_evolve_alloc (4);	
	
	// Set up the parameters as defined in the HW
	Params par = {9.8,200.0,1.0,10.0};
	// Setting up the ODE system: passing function, jacobian, dimension, and parameters
	gsl_odeiv2_system sys = {func, jac, 4, &par};
	
	// Dimension to store - 1000 points
	int dim = 10000;
	// Array to store values
	double values[dim][4];

	// Time and initial condition
	double t = 0.0, t1 = 10.0;
	double h = 1e-6;
	double y[4] = { 0.0, 2.0, 1.0, 0.0 };

	// Main iteration loop
	for (int i = 0; i < dim; i++)
	{
		double ti = i * t1 / dim;
		int status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &t, ti, &h, y);

		if (status != GSL_SUCCESS)
		{
			std::cout << "error, return value = " << status << std::endl;
			break;
		}
		
		// Storing values
		for(int j = 0; j < 4; j++)
		{
			values[i][j] = y[j];
		}
		// Printing values to screen - uncomment if required (for debugging)
		//std::cout << t << "\t" << y[0] << "\t" << y[1]  << "\t" << y[2] << "\t" << y[3] << "\n";
		
	}
	
	// Writing to netCDF file
	writeNetCDF(dim, values);

	// Reading netCDF file
	std::cout << "Time \t X-pos \t Y-pos \t X-vel \t Y-vel \n";
	readNetCDF();

	// Freeing the control memory
	gsl_odeiv2_evolve_free (e);
	gsl_odeiv2_control_free (c);
	gsl_odeiv2_step_free (s);
	return 0;
}


