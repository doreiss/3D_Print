#pragma once
#include <iostream>
#include <vector>

class LatElem
{
public:
	//Constructors
	LatElem(void); //default (0)
	LatElem(int); //initialize value of a cell to given integer

	void setValue(int); //set the value of a cell to given integer (lat gas 1 or 0)
	void setForce(void); //set the force of a cell to given integer (lat gas 0 - 9)
	int getForceDir(void); 
	double getForceMag(void); 
	int getValue(void); //get the value of a cell
	int getNValue(int);  //get the value of a specific neighbour
	void setNeighbours(int, LatElem&); //set the neighbour pointer 
	void setNullNeighbours(void); //set the neighbour pointer to be null
	LatElem* getNeighbour(int i); 
private:
	int value; //Assign an integer value to the cell
	LatElem* neighbours[8]; //Create pointers to the neighbouring cells
	int forceDir; 
	double forceMag;
};

int convertXYDir(int,int); 
/* Naming convention for neighbouring cells around a cell X for 2D lattice gas model


-------------
| 3 | 2 | 1 |
-------------
| 4 | X | 0 |
-------------
| 5 | 6 | 7 |
-------------
*/