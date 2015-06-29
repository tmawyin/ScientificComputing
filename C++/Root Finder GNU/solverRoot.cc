// Function definitions used in solverMain.cc

#include "solverRoot.h"

// This creates the function definition to be used for the solver
double functionDef(double x, void * param) 
{
	return (exp(1 - x*x) - 1) * exp(sin(x));
}

// This creates the derivative of the function
double derivativeDef(double x, void * param) 
{
	return (exp(1-x*x)-1)*exp(sin(x))*cos(x) - 2*x*exp(-x*x+sin(x)+1);
}

void fdfDef(double x, void * params, double * f, double * df)
{
   *f = (exp(1 - x*x) - 1) * exp(sin(x));
   *df = (exp(1-x*x)-1)*exp(sin(x))*cos(x) - 2*x*exp(-x*x+sin(x)+1);
}


// Function to solve for roots using the Newton method
double solveNewton(double x_guess)
{
	double x0, r_expected = 1.0;	
	// Initialize the gsl solver
	gsl_root_fdfsolver* solver;
	// Wrapper to the function
	gsl_function_fdf fwrapper;
	// Allocating the solver to use
	solver = gsl_root_fdfsolver_alloc(gsl_root_fdfsolver_newton);
	// Defines the function and its arguments
	fwrapper.f = &functionDef;
	fwrapper.df = &derivativeDef;
	fwrapper.fdf = &fdfDef;
	fwrapper.params = 0;
	// Calls the solver
	gsl_root_fdfsolver_set(solver, &fwrapper, x_guess);
	int status = 1;
	// Calling the iterations
	std::cout << "Using the solver: " << gsl_root_fdfsolver_name(solver) << "\n";
	std::cout << "iter \t  root \t  error \t error(est)\n";
	for (int iter=0; status and iter < 100; ++iter) 
	{
		gsl_root_fdfsolver_iterate(solver);
		x0 = x_guess;
		x_guess = gsl_root_fdfsolver_root(solver);
		status = gsl_root_test_delta(x_guess, x0, 0, 0.0001);
		if (status == GSL_SUCCESS)
	        std::cout << "Converged:\n";
		std::cout << iter <<"\t"<< x_guess <<"\t" << x_guess - r_expected << "\t" << x_guess - x0 << "\n";
	}
	// Release the solver pointer
	gsl_root_fdfsolver_free(solver);
	return x_guess;
}

// Function to solve for roots using the False position method
double solveFalsepos(double x_lo, double x_hi)
{
	double x_rt;
	// Initialize the gsl solver
	gsl_root_fsolver* solver;
	// Wrapper to the function
	gsl_function fwrapper;
	// Allocating the solver to use
	solver = gsl_root_fsolver_alloc(gsl_root_fsolver_falsepos);
	// Defines the function and its arguments
	fwrapper.function = &functionDef;
	fwrapper.params = 0;
	// Calls the solver
	gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
	int status = 1;
	// Calling the iterations
	std::cout << "Using the solver: " << gsl_root_fsolver_name(solver) << "\n";
	std::cout << "iter  [ lower, upper ]   root    err\n";
	for (int iter=0; status and iter < 100; ++iter) 
	{
		gsl_root_fsolver_iterate(solver);
		// Updating solver values
		x_rt = gsl_root_fsolver_root(solver);
		x_lo = gsl_root_fsolver_x_lower(solver);
		x_hi = gsl_root_fsolver_x_upper(solver);
		status = gsl_root_test_interval(x_lo,x_hi,0,0.0001);
		if (status == GSL_SUCCESS)
	        std::cout << "Converged:\n";
		std::cout << iter <<"\t"<< x_lo <<"\t" << x_hi <<"\t" << x_rt <<"\t"<< x_hi - x_lo << "\n";
	}
	// Release the solver pointer
	gsl_root_fsolver_free(solver);
	return x_rt;
}


// Function to solve for roots using the Brent method (example)
double solveBrent(double x_lo, double x_hi)
{	
	double x_rt;
	// Initialize the gsl solver
	gsl_root_fsolver* solver;
	// Wrapper to the function
	gsl_function fwrapper;
	// Allocating the solver to use
	solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
	// Defines the function and its arguments
	fwrapper.function = &functionDef;
	fwrapper.params = 0;
	// Calls the solver
	gsl_root_fsolver_set(solver, &fwrapper, x_lo, x_hi);
	int status = 1;
	// Calling the iterations
	std::cout << "Using the solver: " << gsl_root_fsolver_name(solver) << "\n";
	std::cout << "iter  [ lower, upper ]   root    err\n";
	for (int iter=0; status and iter < 100; ++iter) 
	{
		gsl_root_fsolver_iterate(solver);
		// Updating solver values
		x_rt = gsl_root_fsolver_root(solver);
		x_lo = gsl_root_fsolver_x_lower(solver);
		x_hi = gsl_root_fsolver_x_upper(solver);
		std::cout << iter <<"\t"<< x_lo <<"\t" << x_hi <<"\t" << x_rt <<"\t"<< x_hi - x_lo << "\n";
		status = gsl_root_test_interval(x_lo,x_hi,0,0.0001);
	}
	// Release the solver pointer
	gsl_root_fsolver_free(solver);
	return x_rt;
}

// Function takes a lower and upper bounds and solves the given equation using both solvers in increasing values given by step
void computeSolvers(double x_lo, double x_hi, double step)
{
	//double maxPoints = (x_hi - x_lo)/step;
	double new_xhi = x_lo + step;
	while (new_xhi <= x_hi)
	{
		solveFalsepos(x_lo, new_xhi);
		solveNewton(new_xhi);
		std::cout << "\n\n";
		new_xhi = new_xhi + step;
	}

}
