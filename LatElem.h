#pragma once
#include <iostream>
#include <vector>

class LatElem
{
public:
	//Constructors
	//default(0)
	LatElem(void);
	//initialize value of a cell to given integer
	LatElem(int);

	//Methods
	//set the value of a cell to given integer (lat gas 1 or 0)
	void setValue(int);
	//set the force of a cell to given integer (lat gas 0 - 9)
	void setForce(void);

	int getForceDir(void); 
	double getForceMag(void); 
	int getValue(void); //get the value of a cell
	int getNValue(int);  //get the value of a specific neighbour
	void setNeighbours(int, LatElem&); //set the neighbour pointer 
	void setNullNeighbours(void); //set the neighbour pointer to be null
	LatElem* getNeighbour(int i); 
private:
	//Value of the cell
	int value; 
	//Pointers to neighbouring cells
	LatElem* neighbours[8];
	//Force acting on element - x direction
	int force_x;
	//Force acting on element - y direction
	int force_y;
};

//Functions
//Convert X,Y values to "Jensen Notation"
int convertXYDir(int,int); 

/* Naming convention for neighbouring cells around a cell X for 2D lattice gas model
"Jensen Notation"

-------------
| 3 | 2 | 1 |
-------------
| 4 | X | 0 |
-------------
| 5 | 6 | 7 |
-------------
*/