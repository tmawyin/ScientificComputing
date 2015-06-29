// Modilarity code - Eigenvalue solver
//
// HW3 - SCMP132
// Created by Tomas Mawyin - 996400531
// 

#include "eigenIO.h"

// Function to print eigenvalues to screen
void print_eigenVals(int n, double* a ) {
        std::cout << "The eigenvalues are: \n";
        for(int i = 0; i < n; i++ ) 
        {
        	std::cout << a[i] << "   ";
        }
        std::cout << "\n";
}

// Power method function: calculates the highest eigenvalue
void PowerMethod(int N, double *l, double w)
{
	// Trying the power method
	// Vector to try: x = unit vector
	double *x = new double[N];
	for(int i=1; i<N; i++)
		x[i] = 1.0;

	double alpha, beta;
	alpha = 1.0;
	beta = 0.0;
	// Initializing temporaty variables
	double *c = new double[10];
	double d=0,temp;
	int counter = 0;
	do
    {
    	// Performing matrix multiplication!!
    	// Note: LDA gets the same value as N
    	int LDA = N;
    	cblas_dgemv(CblasRowMajor,CblasNoTrans,N,N,alpha,l,LDA,x,1,beta,c,1);

    	// Updating the x vector with the new vector X(i+1) = A*x(i)
        for(int i=0;i<N;i++)
            x[i]=c[i];
            
        temp=d;
        d=0;
        
        // Calculating the norm
        for(int i=0;i<N;i++)
        {
            if(fabs(x[i])>fabs(d))
                d=x[i];
        }
        // Updating the possible value of the eigenvalue
        for(int i=0;i<N;i++)
            x[i]/=d;

        // Counts the number of iterations required
        counter++;
            
    }while(fabs(d-temp)>0.00001);

    std::cout<<"Using the power method, the eigenvalue is : "<<d<<std::endl;
    std::cout<<"The residual is : "<<w-d<<std::endl;
    std::cout<<"The number of iterations is : "<<counter<<std::endl;

    delete []x;
    delete []c;
}

// Function to test the Gershgorin theorem:
void Gershgorin(int N, double *l, double *w)
{
	// Testing the Gershgorin cicle theorem: Every eigenvalue of matrix A, lies within at least one Gershgorin disc.
	// center and radius array will keep track of the center point and the radius respectively
	double *radius = new double[N];
	double *center = new double[N];
	// Explicitely initializing he vectors
	for(int i=1; i<N; i++)
	{
		radius[i] = 0.0;
		center[i] = 0.0;
	}
		
	// Looping through the matrix to sum up all the values except the diagonal: First loop goes over the rows
	for(int i=0; i<N; i++)
	{
		// Second loop goes over the columns
		for(int j=0; j<N; j++)
		{
			// The diagonal elements will be position in intervals of 11
			if((i*N+j) % 11 == 0)
			{
				center[i] = l[i*N+j];	// This is the center point of the circle or interval
			}else{
				radius[i] += abs(l[i*N+j]);
			}
		}
		// Now, we can loop through the eigenvalues and check for which ones belong to this interval
		for(int j=0; j<N; j++)
		{
			if(w[j] >= center[i]-radius[i] && w[j] <= center[i]+radius[i])
			{
				std::cout<< "Eigenvalue: " << w[j] << " belongs to the interval " << j+1 
						 << " from: " <<center[i]-radius[i] <<" to " << center[i]+radius[i] << '\n';
			}
		}
		std::cout << "------------\n";
	}

	delete []radius;
	delete []center;
}