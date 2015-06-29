// mymatrix.cc - includes all definitions for the methods prototypes in mymatrix.h

#include "mymatrix.h"

// Constructor: Sets the variables rows and columns.
// Allocates the corresponding memory for the 2D array
// Initializes the array to zeros
MyMatrix::MyMatrix(int r, int c)
{
	// Set the class variables rows and columns
	rows = r;
	columns = c;
	// Allocating memory for the rows in the 2D array
	array = new float*[rows];
	// Loop allocates memory for the columns
	for(int i=0; i<rows; i++)
	{
		array[i] = new float[columns];
	}
}

// Destructor: deallocates memory for the object matrix
MyMatrix::~MyMatrix()
{
	// Deallocates memory from the columns
	for(int i=0; i<rows; i++)
	{
		delete [] array[i];
	}
	// Deallocating memory from the rows
	delete [] array;
}


// get_rows: returns the number of rows in the matrix
int MyMatrix::get_rows()
{
	return rows;
}
//get_columns: returns the number fo columns in the matrix
int MyMatrix::get_columns()
{
	return columns;
}

// set_element: will add "value" to the row,col element
void MyMatrix::set_element(int r, int c, float value)
{
	array[r][c] = value;
}

// output: saves the object matrix to file
void MyMatrix::output(char* file)
{
	std::ofstream resultFile;
	// Opening the file
	resultFile.open (file);
	// Writing to file
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<columns; j++)
		{
			resultFile << array[i][j] << " ";
		}
		resultFile << std::endl;
	}
	// Closing file
	resultFile.close();
}

