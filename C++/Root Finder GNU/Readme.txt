SciNet SCMP132
Homewor #1 - Finding roots
Tomas Mawyin - 996400531

INSTRUCTION:
- Set up environmental variables for GSL and BOOST
- Compile the solver using:
	make

- To compile and run test results from BOOST library use:
	make test


DISCUSSION:

In this homework, we used the False Position and Newton's methods to solve for the roots of the given equation. (Note: I also included Breton mode as an example). The following are some remarks:

- False position method relies on an interval to begin with, this interval must contain the root otherwise the code produces an error.
- Newton's methods uses a derivative, which can sometimes be difficult to implement (or could potentially bring up more numerical errors). It requires only one point as an intial guess which could be troublesome if the slope at that point approaches zero.
- In the simulations if we choose an interval from [0,X] where X ranges from 1 to 10, it is always possible for the False position method to find the root but in some cases Newton's method does not converge or finds a root that is not in the required interval
- When we are able to converge using Newton's method, convergence is usually fast as we can approach the root faster by having the slope at any point
- In terms of stability: As long as the false position method keeps the root within the bracketed interval, the method will be stable and will converge, generally the larger the bracket the slower it will take to converge. Newton's method is stable as long as the initial guess belongs to the set of "stable points" - meaning that at every step we approach towards the root instead of away from it.
- A big disadvantage of implemented this methods using GSL library is that we can only find one root at a time

- In terms of the testing routine implemented with BOOST, both methods show proper convergence when the root is selected as initial guess.
