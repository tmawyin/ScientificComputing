#include <stdlib.h>
#include <stdio.h>
#include "mkl_lapacke.h"

/* Auxiliary routines prototypes */
extern void print_matrix( char* desc, int m, int n, double* a, int lda );

/* Parameters */
#define N 5
#define NSELECT 3
#define LDA N
#define LDZ N

/* Main program */
int main() {
        /* Locals */
        int n = N, il, iu, m, lda = LDA, ldz = LDZ, info;
        double abstol, vl, vu;
        /* Local arrays */
        int ifail[N];
        double w[N], z[LDZ*NSELECT];
        double a[LDA*N] = {
            6.29,  0.00,  0.00,  0.00,  0.00,
           -0.39,  7.19,  0.00,  0.00,  0.00,
            0.61,  0.81,  5.48,  0.00,  0.00,
            1.18,  1.19, -3.13,  3.79,  0.00,
           -0.08, -0.08,  0.22, -0.26,  0.83
        };
        /* Executable statements */
        printf( "LAPACKE_dsyevx (column-major, high-level) Example Program Results\n" );
        /* Negative abstol means using the default value */
        abstol = -1.0;
        /* Set il, iu to compute NSELECT smallest eigenvalues */
        il = 1;
        iu = NSELECT;
        /* Solve eigenproblem */
        info = LAPACKE_dsyevx( LAPACK_COL_MAJOR, 'V', 'I', 'U', n, a, lda,
                        vl, vu, il, iu, abstol, &m, w, z, ldz, ifail );
        /* Check for convergence */
        if( info > 0 ) {
                printf( "The algorithm failed to compute eigenvalues.\n" );
                exit( 1 );
        }
        /* Print the number of eigenvalues found */
        printf( "\n The total number of eigenvalues found:%2i\n", m );
        /* Print eigenvalues */
        print_matrix( "Selected eigenvalues", 1, m, w, 1 );
        /* Print eigenvectors */
        print_matrix( "Selected eigenvectors (stored columnwise)", n, m, z, ldz );
        exit( 0 );
} /* End of LAPACKE_dsyevx Example */

/* Auxiliary routine: printing a matrix */
void print_matrix( char* desc, int m, int n, double* a, int lda ) {
        int i, j;
        printf( "\n %s\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ ) printf( " %6.2f", a[i+j*lda] );
                printf( "\n" );
        }
}