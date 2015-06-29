// File contains all the function definitions to help solve the wave equation, initializes and marches through time
#include "waveStep.h"
#include <cmath>

// Initializes the values of rho as well as the values of x along the grid
void initialize(double* &rho_prev,double* &rho,double* &rho_next,double* &x, double x2, double x1, int ngrid, int npnts)
{
	// Initialize
	for (int i = 0; i < npnts; i++) {
		x[i] = x1 + ((i-1)*(x2-x1))/ngrid; 
		rho[i] = 0.0;
		rho_prev[i] = 0.0;
		rho_next[i] = 0.0;
	}
}

// Excites the values of rho and rho_prev at t=0 
void excite(double* &rho_prev, double* &rho, int npnts)
{
    // Excite
    for (int i = npnts/4 + 1; i < 3*npnts/4; i++) {
        rho[i] = 0.25 - fabs(double(i-npnts/2)/double(npnts));
        rho_prev[i] = rho[i];
    }
}

// Evolves in time to update rho_next based on previous values of rho
void evolve(double* &rho_next, double* rho, double* rho_prev, int ngrid, double c, double dx, double tau, double dt)
{
    // Set zero dirichlet boundary conditions
    rho[0] = 0.0;
    rho[ngrid+1] = 0.0;

    // Evolve
    for (int i = 1; i <= ngrid; i++) {
        double laplacian = pow(c/dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
        double friction = (rho[i] - rho_prev[i])/tau;
        rho_next[i] = 2*rho[i] - rho_prev[i] + dt*(laplacian*dt-friction);
    }
}

