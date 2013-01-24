#pragma once
#include <iostream> 
#include <vector>

class LatElem
{
public:
	LatElem(void); 
	LatElem(int); 
	void setValue(int);
	int getValue(void);
	int getNValue(int); 
	void setNeighbours(int, LatElem&); 
	void setNullNeighbours(void); 
private:
	int value; 
	LatElem* neighbours[8]; 
};