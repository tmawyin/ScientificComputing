// SCMP132 - HW4
// Tomas Mawyin
// Functions that define the evolution step using the full matrix operator

#include "evolveFull.h"

// Constructs the full matrix
double** createMatrix(int npnts, double c, double dx, double tau, double dt)
{
	// Creating the required variables
	double alpha = dt/tau;
	double beta = (c*c*dt*dt)/(dx*dx);

	// Allocating operator matrix
    double** F = new double*[npnts];
    F[0] = new double[npnts*npnts];
    for(int i = 0; i < npnts; i++)
		F[i] = &F[0][i*npnts];
	//Initializing the matrix
	for(int i = 0; i < npnts; i++)
		for(int j = 0; j < npnts; j++)
			F[i][j]=0.0;
	// Creating the full matrix
	for (int i = 0; i < npnts; i++)
	{
		if (i == 0) F[i][i] = 1.0;
		else if ((i > 0) && (i < (npnts - 1)))
		{
			F[i][i-1] = beta;
			F[i][i+1] = beta;
			F[i][i] = 2.0 - alpha - 2.0*beta;
		}else
			F[i][i] = 1.0;
	}
	return F;
}

// Function that perform time marching scheme
void evolveTime(double* rho, double* &rho_prev, double** F, int npnts, double tau, double dt)
{
	// Creating the required variables
	double alpha = dt/tau;
	// Factors to use for CBLAS definition
	double a = 1.0;
	double b = -1.0+alpha;

	cblas_dgemv(CblasRowMajor,CblasNoTrans,npnts,npnts,a,F[0],npnts,rho,1,b,rho_prev,1);

}

// Deallocates opeator matrix F.
void deleteMatrix(double** F)
{
	delete [] F[0];
	delete [] F;
}