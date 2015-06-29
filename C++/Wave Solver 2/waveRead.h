// Header file to containt the prototype of the functions
// It also includes the template as decribe below


#include <iostream>
#include <fstream>

#ifndef WAVEREAD_H
#define WAVEREAD_H

// readParameters: reads input file and sets parameters based on values from the file
// if no file is supplied some default values will be used
void readParameters(int argc, char* argv, double &c, double &tau, double &x1, double &x2, double &runtime, double &dx, double &outtime);

// printValue: prints two values to screen and to a file called: outputFile.txt
// template is created as the first value could either be a string or a double when printing.
template<typename TYPE>
void printValue(TYPE val1, double val2)
{
	// Printing values to screen
	std::cout << val1 << " " << val2 << "\n";
	// Saving values to file
	std::ofstream myfile;
	// Opening the file in appending mode
  	myfile.open ("outputFile.txt", std::ios::out | std::ios::app);
	myfile << val1 << " " << val2 << "\n";
	// Closing file
	myfile.close();
}


#endif
