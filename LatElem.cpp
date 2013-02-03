#include "LatElem.h"
#include <iostream>
#include <cmath>

using namespace std; 

//Default lattice element constructor (empty)
LatElem::LatElem(void) { 
	value = 0; //value = 0
	force[0] = 0;
	force[1] = 0;
	setNullNeighbours(); //null pointer to neighbours
}
//Lattice element constructor with integer value
LatElem::LatElem(int init) {
	value = init; 
	force[0] = 0;
	force[1] = 0;
	setNullNeighbours(); 
}
//Change the value of a lattice element to given integer value
void LatElem::setValue(int init) {
	value = init;
}

//Calculates the force on a given element, given its surrounding elements
void LatElem::setForce(void) { 
	if (value == 0) {
		force[0] = 0;
		force[1] = 0;
		return; 
	}
	force[0] = getNValue(4) - getNValue(0); 
	force[1] = getNValue(6) - getNValue(2);
}

//Returns the direction of the force
int LatElem::getForceDir(void) {
	int forceDir = convertXYDir(force[0],force[1]); 
	return forceDir;
}

//Returns the magnitude of the force
double LatElem::getForceMag(void) {
	double forceMag = (force[0]*force[0] + force[1]*force[1]);
	forceMag = pow(forceMag,0.5); 
	return forceMag; 
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

//Convert components into a xy direction
int convertXYDir(int x, int y) {
	int jensenval;
	if(x > 0) { 
		if (y > 0) jensenval = 1; 
		else if (y < 0) jensenval = 7; 
		else if (y == 0) jensenval = 0; 
	}
	else if (x < 0) { 
		if (y == 0) jensenval = 4; 
		else if (y > 0) jensenval = 3; 
		else if (y < 0) jensenval = 5; 
	} 
	else if (x == 0) { 
		if (y == 0) jensenval = 8; 
		else if (y > 0) jensenval = 2; 
		else if (y < 0) jensenval = 6;
	}
	else { //should never happen, default case
		cout << "ERROR: Problem converting x and y value into Jensen Notation!\n"
			 << "Using default value of 8 (0,0)\n";
		jensenval = 8; 
	}
	return jensenval;
}