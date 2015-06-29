// Modilarity code - Eigenvalue solver
//
// HW3 - SCMP132
// Created by Tomas Mawyin - 996400531
// 

#ifndef EIGENIO_H
#define EIGENIO_H

#include <iostream>
#include <math.h>
#include <cblas.h>
#include <lapacke.h>

// Function used to print the eigenvalues to screen
// n - takes the number of eigenvalues
// a - takes the vector containing the eigenvalues
void print_eigenVals( int n, double* a );

// Function to calculate the highest eigenvalue based on the power method
void PowerMethod(int N, double *l, double w);

// Function to calculate the Gershgorin disc
void Gershgorin(int N, double *l, double *w);

#endif