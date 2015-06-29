// solverRoot main function - runs Newton's and False Position methods

#include "solverRoot.h"

// Main function
int main() {
	double x_lo = 0.0;
	double x_hi = 10.0;
	double x_guess = -5.0;

	double fpos = solveFalsepos(x_lo, x_hi);
	double newt = solveNewton(x_guess);
	
	std::cout << "False position result = " << fpos << "\n";
	std::cout << "Newtons method result = " << newt << "\n";
	std::cout << "\n\n";

	computeSolvers(0.0,10.0,1.0);

	return 0;
}

