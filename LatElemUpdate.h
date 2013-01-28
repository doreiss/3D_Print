#pragma once
#include <iostream>
//#include <cmath>

//Class used to update elements of a lattice, used by LatElem

class LatElemUpdate {
public:
	//constructors
	LatElemUpdate(void); //empty constructor
	LatElemUpdate(int,int); //x and y values

	//functions
	void setForce(int,int); //set force x and y,
	//int getForceArr(int[2]); //get force values as an array - possible?
	//int getForceDir(int); //get force values by graph below
	//int getForceMag(int); //get overall force magnitude
private:
	int forcevalue[2]; //force values
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