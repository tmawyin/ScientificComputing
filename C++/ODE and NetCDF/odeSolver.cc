// Function definitions used in Solver.cc

#include "odeSolver.h"

double sech(double x)
{
	return 1.0/cosh(x);
}

// Describes the system of ODEs
int func (double t, const double y[], double f[],void *params)
{
	// Structure of parameters used
	Params* p = (Params*)params;  
	f[0] = y[2];
	f[1] = y[3];
	f[2] = -p->u*p->h*p->w*cos(y[0])*(1-tanh((p->w*y[1])-(p->w*p->u*sin(y[0])))*tanh((p->w*y[1])-(p->w*p->u*sin(y[0]))));
	f[3] = -p->g + p->h*p->w*(1-tanh((p->w*y[1])-(p->w*p->u*sin(y[0])))*tanh((p->w*y[1])-(p->w*p->u*sin(y[0]))));
	return GSL_SUCCESS;
}

// Jacobian matrix of the system of ODEs
int jac (double t, const double y[], double *dfdy, double dfdt[], void *params)
{
	Params* p = (Params*)params;
	// Defines the gsl matrix 
	gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 4, 4);
	gsl_matrix * m = &dfdy_mat.matrix; 
	// First row of jacobian matrix
	gsl_matrix_set (m, 0, 0, 0.0);
	gsl_matrix_set (m, 0, 1, 0.0);
	gsl_matrix_set (m, 0, 2, 1.0);
	gsl_matrix_set (m, 0, 3, 0.0);
	// Second row
	gsl_matrix_set (m, 1, 0, 0.0);
	gsl_matrix_set (m, 1, 1, 0.0);
	gsl_matrix_set (m, 1, 2, 0.0);
	gsl_matrix_set (m, 1, 3, 1.0);
	// Third row
	gsl_matrix_set (m, 2, 0, -2*p->u*p->h*p->w*cos(y[0])*cos(y[0])*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*tanh((p->w*y[1])-(p->w*p->u*sin(y[0]))) + p->u*p->h*p->w*sin(y[0])*(1 - tanh((p->w*y[1])-(p->w*p->u*sin(y[0])))*tanh((p->w*y[1])-(p->w*p->u*sin(y[0])))));
	gsl_matrix_set (m, 2, 1, 2*p->u*p->h*p->w*p->w*cos(y[0])*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*tanh((p->w*y[1])-(p->w*p->u*sin(y[0]))));
	gsl_matrix_set (m, 2, 2, 0.0);
	gsl_matrix_set (m, 2, 3, 0.0);
	//Fourth row
	gsl_matrix_set (m, 3, 0, 2*p->h*p->w*p->w*p->u*cos(y[0])*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*tanh((p->w*y[1])-(p->w*p->u*sin(y[0]))));
	gsl_matrix_set (m, 3, 1, -2*p->h*p->w*p->w*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*sech((p->w*y[1])-(p->w*p->u*sin(y[0])))*tanh((p->w*y[1])-(p->w*p->u*sin(y[0]))));
	gsl_matrix_set (m, 3, 2, 0.0);
	gsl_matrix_set (m, 3, 3, 0.0);

	dfdt[0] = 0.0;
	dfdt[1] = 0.0;
	dfdt[2] = 0.0;
	dfdt[3] = 0.0;
	return GSL_SUCCESS;
}
