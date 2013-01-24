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
	
	/* 
	int rows = L.rowSize(); 
	int cols = L.colSize(); 
	bool isFirstRow = (rowIndex == 0); 
	bool isFirstCol = (colIndex == 0); 
	bool isFinalRow = ((rowIndex + 1) == rows);
	bool isFinalCol = ((colIndex + 1) == cols);
	
	(isFinalCol					? neighbours[0] = NULL : neighbours[0] = L.getElement(rowIndex,colIndex+1)); 
	(isFirstRow || isFinalCol	? neighbours[1] = NULL : neighbours[1] = L.getElement(rowIndex-1,colIndex+1));
	(isFirstRow					? neighbours[2] = NULL : neighbours[2] = L.getElement(rowIndex-1,colIndex)); 
	(isFirstRow || isFirstCol	? neighbours[3] = NULL : neighbours[3] = L.getElement(rowIndex-1,colIndex-1));
	(isFirstCol					? neighbours[4] = NULL : neighbours[4] = L.getElement(rowIndex,colIndex-1));
	(isFirstCol || isFinalRow	? neighbours[5] = NULL : neighbours[5] = L.getElement(rowIndex+1,colIndex-1));
	(isFinalRow					? neighbours[6] = NULL : neighbours[6] = L.getElement(rowIndex+1,colIndex));
	(isFinalRow || isFinalCol   ? neighbours[7] = NULL : neighbours[7] = L.getElement(rowIndex+1,colIndex+1));
	*/


void LatElem::setNullNeighbours(void) { 
	for (int i = 0; i < 8; i++) { 
		neighbours[i] = NULL; 
	}
}