#pragma once

#include <vector>
#include "CubeElem.h"
using namespace std; 

class CubeArray 
{ 
public: 
	//Default Constructor
	CubeArray (int stacks = 20, int rows = 20, int cols = 20, CubeElem::CubeType init = CubeElem::Empty);  
	
	//Methods: 

	//Returns the number of rows
	int rowSize(void);
	//Returns the number of columns
	int colSize(void);
	//Returns the number of 'stacks' (time)
	int stackSize(void);

private:
	void setCubeNeighbours(void); 
	// 3D array of CubeElem
	vector < vector < vector < CubeElem > > > cubes;

};