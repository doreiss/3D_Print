#include "CubeArray.h"
#include <sstream>
#include <iostream> 
#include <string>
#include <fstream>
using namespace std; 

//Constructor which creates a rows x cols x stacks array of cubes initialized to init
CubeArray::CubeArray( int rows, int cols, int stacks,  CubeElem::CubeType init) {
	for(int i = 0; i < stacks; i++) { 
		vector < vector < CubeElem > > stack; 
		for(int j = 0; j < rows; j++) {
			vector < CubeElem > row; 
			for(int k = 0; k < cols; k++) { 
				CubeElem elem; 
				elem.setType(init); 
				row.push_back(elem); 
			} 
			stack.push_back(row); 
		}
		cubes.push_back(stack); 
	}
	setCubeNeighbours(); 
}

//Constructor which creates a cubeArray from a gas, assigning each LatElem dim cubes in each dimension
//Boolean will remove the boundary of gas model
CubeArray::CubeArray(Gas model, int dim, bool boundariesRemoved) {
	int stacks = model.timeSize(); 
	int rows = 0; 
	int cols = 0;
	if(stacks > 0) {
		rows = model.getLatT(0).rowSize(); 
		cols = model.getLatT(0).colSize(); 
	}
	int n = (dim - 1); 
	int rowsBoolConsider = (boundariesRemoved ? rows - 2 : rows); 
	int colsBoolConsider = (boundariesRemoved ? cols - 2 : cols); 
	int newStacks = 2*n + (n-1)*(stacks-2) + (stacks-1); 
	int newRows = 2*n + (n-1)*(rowsBoolConsider - 2) + (rowsBoolConsider - 1); 
	int newCols = 2*n + (n-1)*(colsBoolConsider - 2) + (colsBoolConsider - 1); 
	cubes.resize(newStacks); 
	for(int i = 0; i < (newStacks); i++) {
		cubes[i].resize(newRows);
		for(int j = 0; j < (newRows); j++) { 
		cubes[i][j].resize(newCols); 
		}
	}
	for(int i = 0; i < stackSize(); i++) { 
		for(int j = 0; j < rowSize(); j++) { 
			for(int k = 0; k < colSize(); k++) { 
				cubes[i][j][k].setType(CubeElem::Empty); 
			}
		} 
	} 
	int stackInd = 0,rowInd,colInd;
	int lowerBound = (boundariesRemoved ? 1:0);
	int rowsUpperBound = (boundariesRemoved ? rows - 1 : rows);
	int colsUpperBound = (boundariesRemoved ? cols - 1 : cols);
	for(int k = 0; k < stacks; k++) { 
		rowInd = 0; 
		Lattice l = model.getLatT(k); 
		vector < vector < CubeElem > > stack; 
		for(int i = lowerBound ; i < rowsUpperBound ; i++) {
			colInd = 0; 
			vector< CubeElem > row;  
			for(int j = lowerBound; j < colsUpperBound; j++) {
				CubeElem::CubeType t = (l.getElement(i,j)->getValue() == 0 ? CubeElem::Empty : CubeElem::Full); 
				if(t == CubeElem::Full) {
					for(int x = 0; x <= n; x++) { 
						for (int y = 0; y <= n; y++) { 
							for(int z = 0; z <= n; z++) {
								cubes[stackInd+x][rowInd+y][colInd+z].setType(t); 
							}
						} 
					}
				}
				colInd += n;
			}
			rowInd += n;; 
		}
		stackInd += n; 
	}
	setCubeNeighbours();
}

//Gets the pointer to cubeElem at row x col x stack
CubeElem* CubeArray::getCube(int rowInd, int colInd, int stackInd) { 
	return &(cubes[stackInd][rowInd][colInd]); 
}

//Sets the CubeType of row x col x stack
void CubeArray::setCubeType(int rowInd, int colInd, int stackInd, CubeElem::CubeType tnew) { 
	CubeElem* elem = getCube(rowInd,colInd,stackInd); 
	elem->setType(tnew);
} 

//Returns the CubeType of CubeElem row x col x stack
CubeElem::CubeType CubeArray::getCubeType(int rowInd, int colInd, int stackInd) { 
	return cubes[stackInd][rowInd][colInd].getType(); 
} 

//Returns the number of rows in the cubeArray
int CubeArray::rowSize(void) { 
	int size = 0; 
	if(stackSize() > 0) { 
		size = cubes[0].size(); 
	} 
	return size;
}

//Returns the number of cols in the CubeArray
int CubeArray::colSize(void) { 
	int size = 0; 
	if(rowSize() > 0) { 
		size = cubes[0][0].size(); 
	}
	return size; 
}

//Returns the number of stacks in the CubeArray
int CubeArray::stackSize(void) { 
	int size = cubes.size(); 
	return size; 
}

//Returns true if the CubeElem at row x col x stackInd is empty
bool CubeArray::isEmpty(int rowInd, int colInd, int stackInd) { 
	CubeElem* elem = getCube(rowInd,colInd,stackInd); 
	return elem->isEmpty(); 
} 

//Prints the cubearray to a triangulated stl file
void CubeArray::print_stl(string filename, string object, double cubeSize) { 
	ofstream outfile(filename);
	outfile << stl_header(object) << endl; 
	for(int k = 0; k < stackSize(); k++) { 
		for(int i = 0; i < rowSize(); i++) { 
			for(int j = 0; j < colSize(); j++) {
				CubeElem* elem = getCube(i,j,k);
				if(!(elem->isEmpty())) {
					vector<int> emptyNInd; 
					for(int nInd = 0; nInd < 6; nInd++) { 
						if((elem->isNEmpty(nInd))) {
							emptyNInd.push_back(nInd); 
						}
					}
					for(unsigned int vecInd = 0; vecInd < emptyNInd.size(); vecInd++) { 
						stl_face(i,j,k,emptyNInd[vecInd],cubeSize,outfile);
					}
				}
			}
		}
	}
	outfile << stl_footer(object) << endl; 
	outfile.close(); 
}

//'Recognizes' the neighbours of each elem in the lattice and sets its neighbours accordingly
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

//Returns a string corresponding to the header of a stl file
string stl_header(string object_name) { 
	string head = " solid "; 
	head += object_name; 
	return head; 
}

//Returns a string corresponding to the footer of a stl file
string stl_footer(string object_name) { 
	string foot = " endsolid "; 
	foot += object_name;
	return foot; 
}

//Prints the stl formatted facet of cube faceInd at rowInd, colInd in outfile
void stl_face(int rowInd, int colInd, int stackInd, int faceInd, double cubeSize, ofstream& outfile) {
	if(outfile.good()) {
		vector < vector < double > > v6 = six_vertex(rowInd, colInd, stackInd, faceInd, cubeSize); 
		vector<double> nVec = normal_vector(faceInd);
		
		outfile << "facet normal "; 
		outfile << scientific << nVec[0] << " "; 
		outfile << scientific << nVec[1] << " "; 
		outfile << scientific << nVec[2] << " " << endl;

		outfile << " outer loop" << endl;
		for(int i = 0; i < 3; i++) { 
			outfile << "  vertex "; 
			for(int j = 0; j < 3; j++) { 
				outfile << scientific << v6[i][j] << " "; 
			}
			outfile << endl; 
		}
		outfile << " endloop" << endl;
		outfile << "endfacet" << endl; 

		outfile << "facet normal "; 
		outfile << scientific << nVec[0] << " "; 
		outfile << scientific << nVec[1] << " "; 
		outfile << scientific << nVec[2] << " " << endl;

		outfile << " outer loop" << endl;
		for(int i = 3; i < 6; i++) { 
			outfile << "  vertex "; 
			for(int j = 0; j < 3; j++) { 
				outfile << scientific << v6[i][j] << " "; 
			}
			outfile << endl; 
		}
		outfile << " endloop" << endl;
		outfile << "endfacet" << endl; 
	}
} 

//Returns a xyz normal vector to given facet
vector < double > normal_vector(int face) { 
	double x = 0.0, y = 0.0, z = 0.0; 
	switch (face) { 
	case 0:
		x = 1.0; 
		break; 
	case 1: 
		z = 1.0; 
		break; 
	case 2: 
		x = -1.0;
		break; 
	case 3: 
		z = -1.0;
		break;
	case 4: 
		y = -1.0;
		break;
	case 5: 
		y = 1.0;
		break;
	default: 
		break; 
	}
	vector<double> normalvec; 
	normalvec.push_back(x); 
	normalvec.push_back(y); 
	normalvec.push_back(z); 
	return normalvec;
}

//Returns the 6 vectors defining the verticies of a triangulated face
vector < vector < double > > six_vertex(int rowInd, int colInd, int stackInd, int faceInd, double cubeSize) { 
	double cx = (colInd*cubeSize);
	double cy = (rowInd*cubeSize);
	double cz = (stackInd*cubeSize); 
	vector < vector < double > > verticies; 
	for(int k = 0; k <= 1; k++) { 
		for (int j = 0; j <= 1; j++) { 
			for (int i = 0; i <= 1; i++) { 
				vector < double > v; 
				double newx = (cubeSize*i);
				newx += cx; 
				double newy = (cubeSize*j); 
				newy += cy; 
				double newz = (cubeSize*k); 
				newz += cz; 
				v.push_back(newx); 
				v.push_back(newy); 
				v.push_back(newz); 
				verticies.push_back(v); 
			} 
		} 
	} 
	vector < vector < double > > rel_vert; 
	switch (faceInd) { 
	case 0:
		rel_vert.push_back(verticies[7]); 
		rel_vert.push_back(verticies[5]); 
		rel_vert.push_back(verticies[1]); 
		rel_vert.push_back(verticies[1]); 
		rel_vert.push_back(verticies[3]);
		rel_vert.push_back(verticies[7]);
		break; 
	case 1:
		rel_vert.push_back(verticies[5]); 
		rel_vert.push_back(verticies[7]); 
		rel_vert.push_back(verticies[6]); 
		rel_vert.push_back(verticies[6]); 
		rel_vert.push_back(verticies[4]);
		rel_vert.push_back(verticies[5]);
		break; 
	case 2:
		rel_vert.push_back(verticies[4]); 
		rel_vert.push_back(verticies[6]); 
		rel_vert.push_back(verticies[2]); 
		rel_vert.push_back(verticies[2]); 
		rel_vert.push_back(verticies[0]);
		rel_vert.push_back(verticies[4]);
		break;
	case 3:
		rel_vert.push_back(verticies[0]); 
		rel_vert.push_back(verticies[2]); 
		rel_vert.push_back(verticies[3]); 
		rel_vert.push_back(verticies[3]); 
		rel_vert.push_back(verticies[1]);
		rel_vert.push_back(verticies[0]);
		break; 
	case 4: 
		rel_vert.push_back(verticies[5]); 
		rel_vert.push_back(verticies[4]); 
		rel_vert.push_back(verticies[0]); 
		rel_vert.push_back(verticies[0]); 
		rel_vert.push_back(verticies[1]);
		rel_vert.push_back(verticies[5]);
		break; 
	case 5:
		rel_vert.push_back(verticies[6]); 
		rel_vert.push_back(verticies[7]); 
		rel_vert.push_back(verticies[3]); 
		rel_vert.push_back(verticies[3]); 
		rel_vert.push_back(verticies[2]);
		rel_vert.push_back(verticies[6]);
		break; 
	default: 
		break; 
	}
	return rel_vert; 
	
}
	/* 

							   V6,V7,V5,V4 (Clockwise from top left)
									|
									|
									v
								  ________
								 /|      /|
								/____ __/ |
				                | |	____| |  
                             	| / 	| /     
								|_______|/
		    
									^
									|
									|
							   V2,V3,V1,V0 (Clockwise from top left)
	*/
	
