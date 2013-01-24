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
//Return the value of a lattice element as an integer
int LatElem::getValue(void) { 
	return value; 
}
//Return the value of the one of the neighbours 
int LatElem::getNValue(int nIndex) {
	return neighbours[nIndex]->getValue(); 
}
void LatElem::setNeighbours(int nIndex, LatElem& neighbour) {
	neighbours[nIndex] = &neighbour; 
}

void LatElem::setNullNeighbours(void) { 
	for (int i = 0; i < 8; i++) { 
		neighbours[i] = NULL; 
	}
}
