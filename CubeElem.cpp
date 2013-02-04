#include "CubeElem.h"

using namespace std; 

CubeElem::CubeElem(CubeType init) {
	type = init; 
	setNullFaceNeighbours(); 
}

CubeElem::CubeType CubeElem::getType(void) { 
	return type; 
}

void CubeElem::setType(CubeType tnew) { 
	type = tnew; 
}

void CubeElem::setFaceNeighbour(int nIndex, CubeElem& neighbour) { 
	face_neighbours[nIndex] = &neighbour; 
} 

bool CubeElem::isNEmpty(int nIndex) {
	return face_neighbours[nIndex]->isEmpty(); 
}

bool CubeElem::isNNull(int nIndex) { 
	return (face_neighbours[nIndex] == NULL); 
}

bool CubeElem::isEmpty(void) { 
	return (type == Empty); 
}

void CubeElem::setNullFaceNeighbours(void) { 
	for (int i = 0; i < 6; i++) { 
		face_neighbours[i] = NULL; 
	} 
} 