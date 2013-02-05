#pragma once //compile only once (replace #ifendf etc)
#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include "LatElem.h"
using namespace std; 
class Lattice
{
public:
	//Constructors:

	//Default
	Lattice(void);
	//Rows, Columns, Initial Value (default 0)
	Lattice(int, int, int init=0);
	//Read from file - Filename, human/.flow file, line of flow file
	Lattice(string, bool, int line=1);
	//Read from an already open stream - Stream name, line number
	//Lattice(ifstream&, int line=1);
	
	//Methods:

	//Set a specific element in the latice - row, column, value
	void setElement(int, int, int);
	//Insert another lattice object into the lattice as a sublattice
	void insertSubLattice(Lattice, int, int);
	//Update all the force elements of the lattice
	void updateForces(void);
	//Return the value of a specific element in the lattice - row, column
	int getElemVal(int,int); 
	//Return a pointer to a specific LatElem object in the lattice - row, column
	LatElem* getElement(int,int);
	//Return the number of rows
	int rowSize(void); 
	//Return the number of columns
	int colSize(void);
	//Return true if a specific element is empty - row, column
	bool isEmpty(int, int);
	//Create a sub lattice
	void setSubLattice(int,int,int,int,int); 
	// first row index, last row index, first column index, last column index 
	void print(void); //cout lattice values

	//Print lattice values to file
	void filePrint(bool,bool,int);
	void filePrint(bool,bool);
	void fileRead(int); //read a lattice from a file lattice.flow
	void fileRead(string,int); //ditto, from a general filename.flow

private: 
	//'Recognise' element neighbours
	void setElementNeighbours(void);
	//2D array of LatElem values
	vector< vector < LatElem > > values; //vector of vectors of lattice elements
};

//Functions:

//Find the largest integer in a vector
int findMax(vector<int>); 
//Convert "Jensen notation" direction to x value
int convertDirX(int); 
//Convert "Jensen notation" direction to y value
int convertDirY(int);

//Check the number of useful lines in Lattice.flow
int fileLines(void);
//Check the number of useful lines in filename.flow
int fileLines(string);
//Check the number of useful lines for a file already open in a given stream
int fileLines(ifstream&);
