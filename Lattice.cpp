#include "Lattice.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std; 

Lattice::Lattice(void) {
	vector<int> emptyrow; 
	emptyrow.push_back(0);
	values.push_back(emptyrow); 
}

Lattice::Lattice(int rows, int columns, int init) {
	vector<int> row; 
	for(int i = 0; i < columns; i++) {
		row.push_back(init);
	}
	for(int i = 0; i < rows; i++) {
		values.push_back(row);
	}
}

Lattice::Lattice(char* file) {
	ifstream ifs(file);
	int fileVal; 
	string line; 
	while(std::getline(ifs,line)) {
		std::istringstream iss(line);
		vector<int> row;
		while(iss >> fileVal) {
			row.push_back(fileVal);
		}
		values.push_back(row);
	}	
}

void Lattice::setElement(int rowInd, int colInd, int init) {
	values[rowInd][colInd] = init; 
}

void Lattice::setSubLattice(int bRowInd, int eRowInd, int bColInd, int eColInd, int init) {
	int rows = 0, columns = 0; 
	columns = values.size(); 
	if (columns > 0) {
		rows = values[0].size();
	}
	if (((eRowInd - bRowInd + 1) >= rows) && ((eColInd - bColInd + 1) >= columns)) {
		for (int i = browInd; i <= eRowInd; i++ ){
			for(int j = bColInd; j <= eColInd; j++) {
				setElement(i,j,init)
			}
		}
	}
}

