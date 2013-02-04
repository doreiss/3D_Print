#include "CubeArray.h"

CubeArray::CubeArray(int rows, int cols, int stacks, CubeElem::CubeType init) {
	for(int i = 0; i < stacks; i++) { 
		vector < vector < CubeElem > > stack; 
		for(int j = 0; j < rows; i++) {
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
	//setCubeNeighbours(); 
}