// Contains equation prototyping for odeSolver.cc

#ifndef ODESOLVER_H
#define ODESOLVER_H

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

// Contains all the required parameters for the solver
// g - gravity
// h - floor hardness
// u - floor unevennes
// w - range of the floor force
struct Params
{
	double g, h, u, w;
};

// Function that returns the hyperbolic secant of a function
double sech(double x);

// Main function definition of the system of ODEs
int func (double t, const double y[], double f[],void *params);

// Jacobian definition of the ODE system
int jac (double t, const double y[], double *dfdy, double dfdt[], void *params);


#endif
