#pragma once
#include <iostream>
#include <vector>

class LatElem
{
public:
	/*
	This enumerated type defines whether or not this LatElem is occupied or not. 
	This will allow for easy extension in the future. 
	*/
	enum LatType { 
		Empty, 
		Full,
		Burning,
	};

	//Constructors :

	//Default : initialize value of a cell to given integer
	LatElem(LatType init = Empty);

	//Methods:
	//Set the value of a cell to given integer (lat gas 1 or 0)
	void setValue(LatType);
	//Calculate the force at this point
	void setForce(void);
	//Return the direction of the force (Jensen notation)
	int getForceDir(void);
	//Return the magnitude of the force vector
	double getForceMag(void);
	//Get burn time
	void setBurnTime(int);
	//Set burn time
	int getBurnTime(void);
	//Is the lattice element empty? - Will simplify some code later
	bool isEmpty(void);
	//Return the value of the cell
	LatType getValue(void);
	//Return the values of neighbouring cells
	LatType getNValue(int);
	//Set the value of neighboruing cells
	void setNeighbours(int, LatElem&);
	//Set the neighbour pointer to be null
	void setNullNeighbours(void); 
	//Gets a pointer which points to neighbour i 
	LatElem* getNeighbour(int i); 

private:

	//Value of the cell
	LatType value; 
	//Pointers to neighbouring cells
	LatElem* neighbours[8];
	//Force acting on element - x direction
	int force_x;
	//Force acting on element - y direction
	int force_y;
	//Timer
	int burn_time;
};

//Functions:

//Convert X,Y values to "Jensen Notation"
int convertXYDir(int,int); 

/* 
Naming convention for neighbouring cells around a cell X for 2D lattice gas model
"Jensen Notation"

-------------
| 3 | 2 | 1 |
-------------
| 4 | X | 0 |
-------------
| 5 | 6 | 7 |
-------------
*/