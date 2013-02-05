#include "CubeArray.h"
CubeArray::CubeArray( int rows, int cols, int stacks,  CubeElem::CubeType init) {
	for(int i = 0; i < stacks; i++) { 
		vector < vector < CubeElem > > stack; 
		for(int j = 0; j < rows; j++) {
			vector < CubeElem > row; 
			for(int k = 0; k < cols; k++) { 
				CubeElem elem; 
				elem.setType(CubeElem::Empty); 
				row.push_back(elem); 
			} 
			stack.push_back(row); 
		}
		cubes.push_back(stack); 
	}
	setCubeNeighbours(); 
}

CubeElem* CubeArray::getCube(int rowInd, int colInd, int stackInd) { 
	return &(cubes[stackInd][rowInd][colInd]); 
}

void CubeArray::setCubeType(int rowInd, int colInd, int stackInd, CubeElem::CubeType tnew) { 
	CubeElem* elem = getCube(rowInd,colInd,stackInd); 
	elem->setType(tnew);
} 

CubeElem::CubeType CubeArray::getCubeType(int rowInd, int colInd, int stackInd) { 
	return cubes[stackInd][rowInd][colInd].getType(); 
} 

int CubeArray::rowSize(void) { 
	int size = 0; 
	if(stackSize() > 0) { 
		size = cubes[0].size(); 
	} 
	return size;
}

int CubeArray::colSize(void) { 
	int size = 0; 
	if(rowSize() > 0) { 
		size = cubes[0][0].size(); 
	}
	return size; 
}

int CubeArray::stackSize(void) { 
	int size = cubes.size(); 
	return size; 
}

void CubeArray::setCubeNeighbours(void) {
	int stacks = stackSize(); 
	int rows = rowSize(); 
	int cols = colSize(); 

	//Iterate over all cubes setting neighbours
	for(int stackIndex = 0; stackIndex < stacks; stackIndex++) {
		for(int rowIndex = 0; rowIndex < rows; rowIndex++) { 
			for(int colIndex = 0; colIndex < cols; colIndex++) { 
			
				//Is it on a boundary? 
			
				bool isFirstStack =	(stackIndex == 0); 
				bool isFirstRow =   (rowIndex == 0);
				bool isFirstCol =   (colIndex == 0);	
				bool isFinalStack = ((stackIndex + 1) == stacks); 
				bool isFinalRow =   ((rowIndex + 1) == rows);
				bool isFinalCol =   ((colIndex + 1) == cols);

				CubeElem* current = &(cubes[stackIndex][rowIndex][colIndex]);

				//Sets neighbours and takes into account boundary conditions
				if (!isFinalCol)	current->setFaceNeighbour(0, cubes[stackIndex][rowIndex][colIndex+1]); 
				if (!isFinalStack)	current->setFaceNeighbour(1, cubes[stackIndex+1][rowIndex][colIndex]); 
				if (!isFirstCol)	current->setFaceNeighbour(2, cubes[stackIndex][rowIndex][colIndex-1]); 
				if (!isFirstStack)	current->setFaceNeighbour(3, cubes[stackIndex-1][rowIndex][colIndex]); 
				if (!isFirstRow)    current->setFaceNeighbour(4, cubes[stackIndex][rowIndex-1][colIndex]); 
				if (!isFinalRow)	current->setFaceNeighbour(5, cubes[stackIndex][rowIndex+1][colIndex]);  
			}
		} 
	}
} 