// SCMP132 - HW4
// Tomas Mawyin
// Functions that define the evolution step using the full matrix operator

#ifndef EVOLVEFULL_H
#define EVOLVEFULL_H

#include <cblas.h>
#include <lapacke.h>

// Creates the full matrix operator.
double** createMatrix(int npnts, double c, double dx, double tau, double dt);

// Function that perform time marching scheme
void evolveTime(double* rho, double* &rho_prev, double** F, int npnts, double tau, double dt);

// Deallocates opeator matrix F.
void deleteMatrix(double** F);

#endif