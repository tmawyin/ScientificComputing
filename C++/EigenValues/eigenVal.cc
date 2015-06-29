// This code calculates the eigenvalues of a 10x10 real matrix
//
// HW3 - SCMP132
// Created by Tomas Mawyin - 996400531
// 

#include "eigenIO.h"

int main(void)
{
	//*** SETTING UP PARAMETERS OF DRIVER ***
	// Number of dimensions of the matrix
	int N = 10;
	// Leading dimension of the matrices 
	int LDA = N;
	int LDZ = N;
	double vl = 0.0;
	double vu = 0.0;
	double abstol = -1.0;
	int il = 1;
	int iu = N;
	int m;
	// Array to store the eigenvalues (w) and the eigenvectors (z)
	double *w = new double[N];
	double *z = new double[N*N];

	int ifail[N];

	// Initializing matrix A
	double a[100] = {
		1.0, 11., 7.0, 9.0, 7.0, 11., 7.0, 9.0, 2.0, 11.,
		11., 4.0, 10., 10., 6.0, 2.0, 9.0, 6.0, 10., 0.0,
		7.0, 10., 3.0, 5.0, 4.0, 4.0, 4.0, 4.0, 6.0, 10.,
		9.0, 10., 5.0, 3.0, 8.0, 8.0, 3.0, 5.0, 1.0, 8.0,
		7.0, 6.0, 4.0, 8.0, 8.0, 10., 5.0, 6.0, 10., 0.0,
		11., 2.0, 4.0, 8.0, 10., 9.0, 4.0, 3.0, 5.0, 11.,
		7.0, 9.0, 4.0, 3.0, 5.0, 4.0, 3.0, 10., 7.0, 2.0,
		9.0, 6.0, 4.0, 5.0, 6.0, 3.0, 10., 11., 1.0, 7.0,
		2.0, 10., 6.0, 1.0, 10., 5.0, 7.0, 1.0, 10., 5.0,
		11., 0.0, 10., 8.0, 0.0, 11., 2.0, 7.0, 5.0, 1.0};

	// For the power method, the array "A" needs to be copied otherwise it gets destroyed in the eigenvalue solver
	double *l = new double [N*N];
	for(int i=0; i < 100; i++)
		l[i] =a[i]; 
	
	// Calling the eigenvalue solver 
	int info = LAPACKE_dsyevx( LAPACK_COL_MAJOR, 'N', 'A', 'U', N, a, LDA, vl, vu, il, iu, abstol, &m, w, z, LDZ, ifail );
	// Checking for error
	if( info > 0 )
	{
		std::cout << "The algorithm failed to compute eigenvalues.\n";
        return 1;
	}

	// Printing eigenvalues to screen
	std::cout << "------------\n";
	print_eigenVals(m, w);

	// Calling the power method:
	std::cout << "------------\n";
	PowerMethod(N, l, w[9]);

	std::cout << "------------\n";

	// Calling the Gershgorin method
	Gershgorin(N, l, w);
	std::cout << "------------\n";	
	
	// Clearing memory from dynamic arrays
	delete [] w;
	delete [] z;
	delete [] l;
	return 0;
}