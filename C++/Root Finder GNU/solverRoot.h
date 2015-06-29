#ifndef SOLVERROOT_H
#define SOLVERROOT_H

#include <iostream>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>

// Equation prototype
double functionDef(double x, void * param);
// Derivative of equation
double derivativeDef(double x, void * param) ;
// Setting function values - required for Newton's method
void fdfDef(double x, void * params, double * f, double * df);

// Root solvers:
// Newtons' methond
double solveNewton(double x_guess);
// False position method
double solveFalsepos(double x_lo, double x_hi);
// Brent method
double solveBrent(double x_lo, double x_hi);

// Function that uses solvers from a low to a high values increasing by step size
void computeSolvers(double x_lo, double x_hi, double step);

#endif
