#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <istream>
#include "CubeElem.h"
#include "Gas.h"
#include "Lattice.h"
#include "Vec3.h"
using namespace std; 

class CubeArray 
{ 
public: 
	//Constructors: 

	//Default Constructor
	CubeArray (int rows = 20, int cols = 20, int stacks = 20,  CubeElem::CubeType init = CubeElem::Empty); 
	//Reads the CubeArray in from a predefined gas
	CubeArray (Gas, int dim = 3, bool boundariesRemoved = true); 


	//Methods: 

	//Returns a pointer to CubeElem at row,col,stack
	CubeElem* getCube(int,int,int);
	//Sets the cube at row,col,stack's type
	void setCubeType(int,int,int,CubeElem::CubeType);
	//Gets the cube at row,col,stack's type
	CubeElem::CubeType getCubeType(int,int,int); 
	//Returns the number of rows
	int rowSize(void);
	//Returns the number of columns
	int colSize(void);
	//Returns the number of 'stacks' (time)
	int stackSize(void);
	//Checks if cube at row,col,stack is empty
	bool isEmpty(int,int,int); 

private:
	//'Recognizes' the cube neighbours and assigns them
	void setCubeNeighbours(void); 
	// 3D array of CubeElem
	vector < vector < vector < CubeElem > > > cubes;

};

//Functions: 

//Gives the normal vector to face described by int
Vec3 normal_vector(int);
