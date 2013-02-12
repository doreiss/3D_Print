#include "CubeElem.h"

using namespace std;

//Constructor for CubeElem wtih type init
CubeElem::CubeElem(CubeType init) {
	type = init; 
	setNullFaceNeighbours(); 
}

//Returns the type of this CubeElem
CubeElem::CubeType CubeElem::getType(void) { 
	return type; 
}

//Set the type of this CubeElem
void CubeElem::setType(CubeType tnew) { 
	type = tnew; 
}

//Set the pointer to neighbour nIndex
void CubeElem::setFaceNeighbour(int nIndex, CubeElem& neighbour) { 
	face_neighbours[nIndex] = &neighbour; 
} 

//Returns true if the neighbour is empty
bool CubeElem::isNEmpty(int nIndex) {
	bool status = true; 
	if(!isNNull(nIndex)) { 
		status = face_neighbours[nIndex]->isEmpty(); 
	}
	return status; 
}

//Returns true if neighbour is null 
bool CubeElem::isNNull(int nIndex) { 
	return (face_neighbours[nIndex] == NULL); 
}

//Returns true if this is empty
bool CubeElem::isEmpty(void) { 
	return (type == Empty); 
}

//Sets all the members to NULL
void CubeElem::setNullFaceNeighbours(void) { 
	for (int i = 0; i < 6; i++) { 
		face_neighbours[i] = NULL; 
	} 
} 