#include "LatElem.h"
#include <iostream>

using namespace std; 

//Default lattice element constructor (empty)
LatElem::LatElem(void) { 
	value = 0; //value = 0
	forceDir = 8;
	forceMag = 0.0; 
	setNullNeighbours(); //null pointer to neighbours
	
}
//Lattice element constructor with integer value
LatElem::LatElem(int init) {
	value = init; 

	forceDir = 8;
	forceMag = 0.0;
	setNullNeighbours(); 
}
//Change the value of a lattice element to given integer value
void LatElem::setValue(int init) {
	value = init;
}

//Calculates the force on a given element, given its surrounding elements
void LatElem::setForce(void) { 
	if (value == 0) {
		return; 
	} 
	int f_x = getNValue(4) - getNValue(0); 
	int f_y = getNValue(6) - getNValue(2);
	forceDir = convertXYDir(f_x,f_y); 
	forceMag = pow((f_x*f_x+f_y*f_y),0.5); 
}


int LatElem::getForceDir(void) { 
	return forceDir; 
}

//Return the value of a lattice element as an integer
int LatElem::getValue(void) { 
	return value; 
}
//Return the value of the one of the neighbours 
int LatElem::getNValue(int nIndex) {
	if (neighbours[nIndex] == NULL) return 0; 
	return neighbours[nIndex]->getValue(); 
}

//Return a Neighbour
LatElem* LatElem::getNeighbour(int i) {
	return neighbours[i];
}

//Set the value of a specific neighbouring cell
void LatElem::setNeighbours(int nIndex, LatElem& neighbour) {
	neighbours[nIndex] = &neighbour; 
}

//Set the neighbours of the lattice element to be null-pointers
void LatElem::setNullNeighbours(void) { 
	for (int i = 0; i < 8; i++) { 
		neighbours[i] = NULL; 
	}
}


int convertXYDir(int x,int y) { 
	if( x>0 ) { 
		if (y == 0) return 0; 
		if (y > 0) return 1; 
		if (y < 0) return 7; 
	}
	else if (x < 0) { 
		if (y == 0) return 4; 
		if (y > 0) return 3; 
		if (y < 0) return 5; 
	} 
	else if (x == 0) { 
		if (y == 0) return 8; 
		if (y > 0) return 2; 
		if (y < 0) return 6; 
	}
	else return 8; 
}

