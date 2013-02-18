#include "LatElem.h"
#include <iostream>
#include <cmath>

using namespace std; 

//Lattice element constructor with integer value
LatElem::LatElem(LatType init) {
	value = init;
	burn_time = 0;
	force_x = 0;
	force_y = 0;
	setNullNeighbours(); 
}

//Change the value of a lattice element to given integer value
void LatElem::setValue(LatType init) {
	value = init;
}

//Calculates the force on a given element, given its surrounding elements
void LatElem::setForce(void) { 
	if (value == 0) {
		force_x = 0;
		force_y = 0;
		return; 
	}
	force_x = getNValue(4) - getNValue(0); 
	force_y = getNValue(6) - getNValue(2);
}

//Returns the direction of the force
int LatElem::getForceDir(void) {
	int forceDir = convertXYDir(force_x,force_y); 
	return forceDir;
}

//Returns the magnitude of the force
double LatElem::getForceMag(void) {
	double forceMag = (force_x*force_x + force_y*force_y);
	forceMag = pow(forceMag,0.5); 
	return forceMag; 
}

//Get burn time
void LatElem::setBurnTime(int newval) {
	burn_time = newval;
}

//Set burn time
int LatElem::getBurnTime(void) {
	return burn_time;
}

//Return true if the lattice element has Latype::Empty
bool LatElem::isEmpty(void) {
	bool toreturn = false;
	if (getValue() == LatType::Empty) {
		toreturn = true;
	}
	return toreturn;
}

//Return the value of a lattice element as an integer
LatElem::LatType LatElem::getValue(void) { 
	return value; 
}

//Return the value of the one of the neighbours
LatElem::LatType LatElem::getNValue(int nIndex) {
	if (neighbours[nIndex] == NULL) return LatElem::Empty; 
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