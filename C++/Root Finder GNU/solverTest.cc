// Testing routines with BOOST library

#define BOOST_TEST_MODULE testingSolver
#include <boost/test/included/unit_test.hpp>

#include "solverRoot.h"

BOOST_AUTO_TEST_SUITE(testing)
BOOST_AUTO_TEST_CASE(TestFalse)
{
	double x_lo = 1.0;
	double x_hi = 1.0;
	double fpos = solveFalsepos(x_lo, x_hi);
	BOOST_CHECK(fpos == 1.0);
}

BOOST_AUTO_TEST_CASE(TestNewton)
{
	double x_guess = 1.0;
	double newt = solveNewton(x_guess);
	BOOST_CHECK(newt == 1.0);
}
BOOST_AUTO_TEST_SUITE_END()
