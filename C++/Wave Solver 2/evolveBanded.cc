// SCMP132 - HW4
// Tomas Mawyin
// Functions that define the evolution step using the banded matrix operator

#include "evolveBanded.h"

// Creates the banded matrix operator: 3 bands are required including points for boundary conditions
double** createMatrix(int npnts, double c, double dx, double tau, double dt)
{
	// Creating the required variables
	double alpha = dt/tau;
	double beta = (c*c*dt*dt)/(dx*dx);

	// Allocating operator matrix
    double** F = new double*[3];
    F[0] = new double[3*npnts];
    for(int i = 0; i < 3; i++)
		F[i] = &F[0][i*npnts];
	//Initializing the matrix
	for(int i = 0; i < npnts; i++)
	{
		F[0][i] = beta;
		F[1][i] = 2.0 - alpha - 2.0*beta;
		F[2][i] = beta;
	}
		
	// Adding the necesary zeros to the matrix
	F[0][0] = 0.0; F[0][1] = 0.0;
	F[2][npnts-1] = 0.0; F[2][npnts-2] = 0.0;
	F[1][0] = 1.0; F[1][npnts-1] = 1.0;
	
	return F;
}

// Evolve function. Provides matrix multiplication between operator and vector of points
// Time marching scheme
void evolveTime(double* rho, double* &rho_prev, double** F, int npnts, double tau, double dt)
{
	// Creating the required variables
	double alpha = dt/tau;
	// Factors to use for CBLAS definition
	double a = 1.0;
	double b = -1.0+alpha;

	//cblas_dgemv(CblasRowMajor,CblasNoTrans,npnts,npnts,a,F[0],npnts,rho,1,b,rho_prev,1);
	cblas_dgbmv(CblasRowMajor,CblasNoTrans,3,npnts,1,2,a,F[0],npnts,rho,1,b,rho_prev,1);
}

// Deallocates the matrix operator F
void deleteMatrix(double** F)
{
	delete [] F[0];
	delete [] F;
}