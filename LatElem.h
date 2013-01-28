#pragma once
#include <iostream>
#include <vector>
#include "LatElemUpdate.h"

class LatElem
{
public:
	//Constructors
	LatElem(void); //default (0)
	LatElem(int); //initialize value of a cell to given integer

	void setValue(int); //set the value of a cell to given integer (lat gas 1 or 0)
	void setForce(void); //set the force of a cell to given integer (lat gas 0 - 9)
	LatElemUpdate getForce(void); 
	int getValue(void); //get the value of a cell
	int getNValue(int);  //get the value of a specific neighbour
	LatElemUpdate getNForce(int); // gets the force of a a specific neighbour
	void setNeighbours(int, LatElem&); //set the neighbour pointer 
	void setNullNeighbours(void); //set the neighbour pointer to be null
private:
	int value; //Assign an integer value to the cell
	int move;
	LatElem* neighbours[8]; //Create pointers to the neighbouring cells
	LatElemUpdate force; //Force value
};

/* Naming convention for neighbouring cells around a cell X for 2D lattice gas model


-------------
| 3 | 2 | 1 |
-------------
| 4 | X | 0 |
-------------
| 5 | 6 | 7 |
-------------
*/