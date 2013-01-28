#include "LatElem.h"
#include <iostream>

using namespace std; 

//Default lattice element constructor (empty)
LatElem::LatElem(void) { 
	value = 0; //value = 0
	setNullNeighbours(); //null pointer to neighbours
	
}
//Lattice element constructor with integer value
LatElem::LatElem(int init) {
	value = init; 
	setNullNeighbours(); 
}
//Change the value of a lattice element to given integer value
void LatElem::setValue(int init) {
	value = init;
}

//Calculates the force on a given element, given its surrounding elements
void LatElem::setForce(void) { 
	if (value = 0) {
		return ; 
	} 

	int f_x = getNValue(0) - getNValue(4); 
	int f_y = getNValue(2) - getNValue(6);
	LatElemUpdate f(f_x,f_y);
	force = f;
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
