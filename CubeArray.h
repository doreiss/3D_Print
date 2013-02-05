#pragma once

#include <vector>
#include "CubeElem.h"
using namespace std; 

class CubeArray 
{ 
public: 
	//Default Constructor
	CubeArray (int rows = 20, int cols = 20, int stacks = 20,  CubeElem::CubeType init = CubeElem::Empty);  
	
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

	//Prints to stl 
	void print_stl(char* filename); 

private:
	//'Recognizes' the cube neighbours and assigns them
	void setCubeNeighbours(void); 
	// 3D array of CubeElem
	vector < vector < vector < CubeElem > > > cubes;

};