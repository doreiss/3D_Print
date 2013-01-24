#include "LatElem.h"
#include <iostream>

using namespace std; 

LatElem::LatElem(void) { 
	value = 0;
	setNullNeighbours();
	
}
LatElem::LatElem(int init) {
	value = init; 
	setNullNeighbours(); 
}
void LatElem::setValue(int init) {
	value = init;
}
int LatElem::getValue(void) { 
	return value; 
}
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
