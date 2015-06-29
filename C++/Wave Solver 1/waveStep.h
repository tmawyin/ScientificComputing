#ifndef WAVESTEP_H
#define WAVESTEP_H

// initialize: Use this function to initialize x values along the grid
// as well as rho_ to zero. It uses values initialized by the user
void initialize(double* &rho_prev,double* &rho,double* &rho_next,double* &x, double x2, double x1, int ngrid, int npnts);

// excite: function to excite the wave prior to stepping in time
// This function updates rho_prev and rho
void excite(double* &rho_prev, double* &rho, int npnts);

// evolve: function to evolve in time
// This function updates rho_next based on previous values of rho
void evolve(double* &rho_next, double* rho, double* rho_prev, int ngrid, double c, double dx, double tau, double dt);

#endif
