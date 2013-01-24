#pragma once
#include <iostream> 
#include <vector>

class LatElem
{
public:
	//Constructors
	LatElem(void); //default (0)
	LatElem(int); //initialize value, set 
	void setValue(int);
	int getValue(void);
	int getNValue(int); 
	void setNeighbours(int, LatElem&); 
	void setNullNeighbours(void); 
private:
	int value; //Assign an integer value to the cell
	LatElem* neighbours[8]; //Create pointers to the neighbouring cells
};