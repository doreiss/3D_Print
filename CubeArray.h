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
using namespace std; 

class CubeArray 
{ 
public: 
	//Constructors: 

	//Default Constructor
	CubeArray (int rows = 20, int cols = 20, int stacks = 20,  CubeElem::CubeType init = CubeElem::Empty); 
	//Reads the CubeArray in from a predefined gas
	CubeArray (Gas); 


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

	//Prints to stl 
	void print_stl(string, string = "OBJNAME", double = 1.0); 

private:
	//'Recognizes' the cube neighbours and assigns them
	void setCubeNeighbours(void); 
	// 3D array of CubeElem
	vector < vector < vector < CubeElem > > > cubes;

};

//Functions: 

//Generates a stl header
string stl_header(string);
//Generates a stl footer
string stl_footer(string);
//Generates a stl facet
void stl_face(int,int,int,int,double,ofstream&); 

//Gives the normal vector to face described by int
vector<double> normal_vector(int);
vector < vector < double > > six_vertex(int,int,int,int,double); 