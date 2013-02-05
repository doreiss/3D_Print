#include "CubeArray.h"
#include <sstream>
#include <iostream> 
#include <string>
#include <fstream>
using namespace std; 
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

CubeArray::CubeArray(Gas G) {

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

bool CubeArray::isEmpty(int rowInd, int colInd, int stackInd) { 
	CubeElem* elem = getCube(rowInd,colInd,stackInd); 
	return elem->isEmpty(); 
} 

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

string stl_header(string object_name) { 
	string head = " solid "; 
	head += object_name; 
	return head; 
}

string stl_footer(string object_name) { 
	string foot = " endsolid "; 
	foot += object_name;
	return foot; 
}

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
	