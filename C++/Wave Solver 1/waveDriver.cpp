// File contains the main function and driver to calculate wave equation
#include "waveRead.h"
#include "waveStep.h"

int main(int argc, char* argv[])
{
	// ----- Variable Definition ----- 
	// Physical parameters
	double  c;		// wave speed
	double  tau;	// damping time
	double  x1;		// left most x value
	double  x2;		// right most x value

	// Simulation parameters
	double  runtime;	// how long should the simulation try to compute?
	double  dx;    		// spatial grid size

	// Output parameters
	double  outtime; 	// how often should a snapshot of the wave be written out?
	
	// Calls function to read from file or initiliaze variables
	readParameters(argc, argv[1], c, tau, x1, x2, runtime, dx, outtime);


    // Derived parameters
    int     ngrid   = (x2-x1)/dx;  // number of x points
    int     npnts   = ngrid + 2;   // number of x points including boundary points
    double  dt      = 0.5*dx/c;    // time step size
    int     nsteps  = runtime/dt;  // number of steps of that size to reach runtime
    int     nper    = outtime/dt;  // how many step s between snapshots

    // Report all the values to file and screen
	printValue("#c       ",c);
	printValue("#tau     ",tau);
    printValue("#x1      ",x1);
	printValue("#x2      ",x2);
	printValue("#runtime ",runtime);
	printValue("#dx      ",dx);
	printValue("#outtime ",outtime); 
	printValue("#ngrid   ",ngrid);
	printValue("#dt      ",dt);
	printValue("#nsteps  ",nsteps);
	printValue("#nper    ",nper);

    // Define and allocate arrays
    double* rho_prev = new double[npnts]; // time step t-1
    double* rho      = new double[npnts]; // time step t
    double* rho_next = new double[npnts]; // time step t+1
    double* x        = new double[npnts]; // x values


	// Initializes rho and x values
	initialize(rho_prev, rho, rho_next, x, x2, x1, ngrid, npnts);

	// Calls excite function to update rho_prev and rho
	excite(rho_prev, rho, npnts);

    // Output initial signal
	printValue("\n# t = ",0);
    for (int i = 1; i <= ngrid; i++) 
		printValue(x[i],rho[i]);

    // Take timesteps
    for (int s = 0; s < nsteps; s++) {

		// Calls evolve function to update rho_next
		evolve(rho_next, rho, rho_prev, ngrid, c, dx, tau, dt);

        // Rotate array pointers so t+1 becomes the new t etc.
        double* temp = rho_prev;
        rho_prev = rho;
        rho      = rho_next;
        rho_next = temp;  

        // Output density
        if ((s+1)%nper == 0) {
			printValue("\n\n# t = ",s*dt);
            for (int i = 1; i <= ngrid; i++) 
				printValue(x[i],rho[i]);
        }
    }
	
    // Deallocate memory
    delete[] rho_prev;
    delete[] rho;
    delete[] rho_next;
    delete[] x;

    return 0;
}
