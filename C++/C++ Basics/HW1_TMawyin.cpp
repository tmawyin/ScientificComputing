// SCMP122 - Homework 1
// Tomas Mawyin - 996400531
// -----------------------------

// Description: This program will calculate and print the tanh(2x) for x in the range [-2,2]
// Compile: g++ HW1_TMawyin.cpp -o HW1_TMawyin -Wall -O2
// Execute: ./HW1_TMawyin

#include <iostream>		// Used to print to screen
#include <math.h>       // Used to compute hyperbolic tangent
#include <fstream>		// Used to print to file

using namespace std;

// calcTanh: Function to calculate the hyperbolic tangent of x
double calcTanh(double x)
{
	return tanh(x);
}


// Main function: Divides the range in intervals and calls the function to compute hyperbolic tangent
int main()
{
	// Variable definitions
	double lowBound = -2.0;	// Lower value of range
	double highBound = 2.0;	// Higher value of range
	double dx;				// Size of interval (we will use 100 intervals)
	double nxtPoint;		// next point used to calculate interval
	double x, y;			// stores y = tanh(x)
	ofstream ResultFile;		// Uses file handle "ResultFile"

	// Calculating the interval size
	dx = (highBound - lowBound)/100;
	
	// Header to print to screen
	cout << "x\t|\ty" << endl;	
	cout << "---------------------" << endl;

	// Opens the result file to store x and y values
	ResultFile.open ("Results.txt");	
	ResultFile << "x \t\t|\t\t y" << endl;	
	ResultFile << "---------------------" << endl;

	// Loop to calculate and write the tanh to screen and to file
	for(double i=lowBound; i<highBound; i=i+dx)
	{
		// x is the middle point of each interval
		nxtPoint = i + dx;
		x = (i + nxtPoint)/2;
		// y gets the result from the calcTanh function
		y = calcTanh(x);
		// Printing values to screen
		cout << x << "\t|\t"<< y << endl;
		// Printing values to file
		ResultFile << x << "\t|\t"<< y << endl;
	}
	// Closing the file
	ResultFile.close();
	return 0;
}
