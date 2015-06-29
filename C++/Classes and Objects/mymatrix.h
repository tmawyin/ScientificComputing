// mymatrix.h - prototype methods for matrix class
#include <iostream>
#include <fstream>

#ifndef MYMATRIX_H
#define MYMATRIX_H

class MyMatrix{
private:
	int rows;	// contains number of rows in matrix
	int columns;	// contains number of columns in matrix
	float** array;	// contains the matrix object (2D array)

public:
	// Constructor: Sets the variables rows and columns. Allocates memory for the object matrix
	MyMatrix(int r, int c);
	// Destructor: deallocates memory for the object matrix
	~MyMatrix();

	// get_rows: returns the number of rows in the matrix
	int get_rows();
	//get_columns: returns the number fo columns in the matrix
	int get_columns();

	// set_element: will add "value" to the r,c element
	void set_element(int r, int c, float value);
	// output: saves the object matrix to file
	void output(char* file);
};

#endif
