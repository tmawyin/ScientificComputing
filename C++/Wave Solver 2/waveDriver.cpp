// SCMP132 - HW4
// Tomas Mawyin
//
// File contains the main function and driver to calculate wave equation
#include "waveRead.h"
#include "waveStep.h"
#include "evolveFull.h"
#include "evolveBanded.h"
#include "ticktock.h"
#include "ioFile.h"

// Function in charge of running the wave solver. 
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
    int     sizeT   = int(runtime+1);

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
    double* t        = new double[sizeT]; // stores all times "t"
    // Allocating the matrix that will contain all instances of rho
    double** rhoFull = new double*[npnts];
    rhoFull[0] = new double[npnts*sizeT];
    for(int i = 0; i < npnts; i++)
        rhoFull[i] = &rhoFull[0][i*sizeT];
    //Initializing the matrix
    for(int i = 0; i < npnts; i++)
        for(int j = 0; j < sizeT; j++)
            rhoFull[i][j]=0.0;

    // Initializing the time vector
    t[0] = 0.0;
    
	// Initializes rho and x values
	initialize(rho_prev, rho, rho_next, x, x2, x1, ngrid, npnts);

	// Calls excite function to update rho_prev and rho
	excite(rho_prev, rho, npnts);
    saveRho(npnts, 0, rhoFull, rho);
	
    /*
    // Output initial signal to text file
	printValue("\n# t = ",0);
    for (int i = 1; i <= ngrid; i++) 
		printValue(x[i],rho[i]);
	*/

    // Creating the matrix: Full or Banded depending on the Makefile call
    double** F = createMatrix(npnts, c, dx, tau, dt);

    // Timer to measure full time marching scheme
    TickTock timer;
    timer.tick(); 

    // Take timesteps
    int timeCount = 1;
    for (int s = 0; s < nsteps; s++) {

		// Calls evolve function to update rho_next: From HW2
		// evolve(rho_next, rho, rho_prev, ngrid, c, dx, tau, dt);

		// Calls evolveFull function: Uses full or banded matrix multiplication
    	rho[0] = 0.0;
    	rho[ngrid+1] = 0.0;
		evolveTime(rho, rho_prev, F, npnts, tau, dt);

        // Rotate array pointers so t+1 becomes the new t etc.
        double* temp = rho_prev;
        rho_prev = rho;
        rho = temp;

        
        // Output to text or binary file
        if ((s+1)%nper == 0) {
            t[timeCount] = s*dt;
            saveRho(npnts, timeCount, rhoFull, rho);
            timeCount++;
            
            /*Comment out if required to print to screen and save to text file (HW2)
			printValue("\n\n# t = ",s*dt);
                for (int i = 1; i <= ngrid; i++) 
                    printValue(x[i],rho[i]);
            */
        }
        
    }
    timer.tock("Total time-marching time:");

    // Writes variables to netCDF file. 
    writeNetCDF(npnts, sizeT, t, rhoFull, x);
    readNetCDF();

    // Deallocate memory
    delete[] rho_prev;
    delete[] rho;
    delete[] rho_next;
    delete[] x;
    delete [] t;
    delete [] rhoFull[0];
    delete [] rhoFull;
	deleteMatrix(F);

    return 0;
}
