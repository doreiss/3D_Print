#pragma once //compile only once (replace #ifendf etc)
#include <iostream>
#include <vector> 
#include "LatElem.h"
using namespace std; 
class Lattice
{
public:
	//Constructors
	Lattice(void);
	Lattice(int, int, int);
	Lattice(char*);
	//Functions
	void setElement(int, int, int);
	void insertSubLattice(Lattice, int, int);
	void updateForces(void); 
	int getElemVal(int,int);
	LatElem getElement(int,int);
	int rowSize(void); 
	int colSize(void); 
	bool isEmpty(int, int);
	void setSubLattice(int,int,int,int,int);
	void print(void);
private: 
	void setElementNeighbours(void); //does thi
	vector< vector < LatElem > > values; //vector of vectors of lattice elements
};
