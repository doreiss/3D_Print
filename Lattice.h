#pragma once //compile only once (replace #ifendf etc)
#include <iostream>
#include <vector> 
#include "LatElem.h"
using namespace std; 
class Lattice
{
public:
	Lattice(void); //Default constructor
	Lattice(int, int, int);
	Lattice(char*);
	void setElement(int, int, int);
	int getElemVal(int,int);
	LatElem getElement(int,int);
	int rowSize(void); 
	int colSize(void); 
	bool isEmpty(int, int);
	void setSubLattice(int,int,int,int,int);
	void print(void);
private: 
	void setElementNeighbours(void); 
	vector< vector < LatElem > > values; 
};
