#include "LatElem.h"
#include <iostream>

using namespace std; 

//Default lattice element constructor (empty)
LatElem::LatElem(void) { 
	value = 0; //value = 0
	force = LatElemUpdate(); 
	setNullNeighbours(); //null pointer to neighbours
	
}
//Lattice element constructor with integer value
LatElem::LatElem(int init) {
	value = init; 

	force = LatElemUpdate(); 
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
	LatElemUpdate f(f_x,f_y); 
	force = f; 
}

LatElemUpdate LatElem::getForce(void) { 
	return force; 
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

//Return the Force Object of a LatElem
LatElemUpdate LatElem::getNForce(int nIndex) {
	return neighbours[nIndex]->force; 
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
