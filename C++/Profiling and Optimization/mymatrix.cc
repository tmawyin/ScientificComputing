// mymatrix.cc - includes all definitions for the methods prototypes in mymatrix.h

#include "mymatrix.h"
#include <iostream>
#include <fstream>

// Constructor: Sets the variables rows and columns.
// Allocates the corresponding memory for the 2D array
// Initializes the array to zeros
MyMatrix::MyMatrix(int r, int c)
{
	// Set the class variables rows and columns
	row = r;
	col = c;
	// Allocating memory for the rows in the 2D array
	el = new double*[row];
	// Loop allocates memory for the columns
	for(int i=0; i<row; i++)
	{
		el[i] = new double[col];
	}
}

// Destructor: deallocates memory for the object matrix
MyMatrix::~MyMatrix()
{
	// Deallocates memory from the columns
	for(int i=0; i<row; i++)
	{
		delete [] el[i];
	}
	// Deallocating memory from the rows
	delete [] el;
}


// get_rows: returns the number of rows in the matrix
int MyMatrix::get_rows()
{
	return row;
}
//get_columns: returns the number fo columns in the matrix
int MyMatrix::get_columns()
{
	return col;
}

// set_element: will add "value" to the row,col element
void MyMatrix::set_element(int i, int j, double value)
{
	el[i][j] = value;
}

// output: saves the object matrix to file
void MyMatrix::output(const char* filename)
{
	std::ofstream resultFile;
	// Opening the file
	resultFile.open (filename);
	// Writing to file
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			resultFile << el[i][j] << " ";
		}
		resultFile << std::endl;
	}
	// Closing file
	resultFile.close();
}

// get_element: returns the element located in row i, and column j
double MyMatrix::get_element(int i, int j)
{
	return el[i][j];
}

double** MyMatrix::get_pointer()
{
	return el;
}
