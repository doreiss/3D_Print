#pragma once
#include <iostream>
#include <vector> 
#include "LatElem.h"
using namespace std; 
class Lattice
{
public:
	Lattice(void); 
	Lattice(int, int, int);
	Lattice(char*);
	void setElement(int, int, int);
	void setElementNeighbours(void); 
	int getElemVal(int,int);
	LatElem getElement(int,int);
	int rowSize(void); 
	int colSize(void); 
	bool isEmpty(int, int);
	void setSubLattice(int,int,int,int,int);
	void print(void);
private: 
	vector< vector < LatElem > > values; 
};
