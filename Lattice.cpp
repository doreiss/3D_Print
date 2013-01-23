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

int	Lattice::getElement(int rowInd, int colInd) {
	return values[rowInd][colInd]; 
}


void Lattice::setSubLattice(int bRowInd, int eRowInd, int bColInd, int eColInd, int init) {
	int rows = 0, columns = 0; 
	columns = values.size(); 
	if (columns > 0) {
		rows = values[0].size();
	}
	cout << columns << '\t' << rows << endl; 
	if (((eRowInd+1) <= rows) && ((eColInd+1) <= columns)) {
		for (int i = bRowInd; i <= eRowInd; i++ ){
			for(int j = bColInd; j <= eColInd; j++) {
				setElement(i,j,init);
			}
		}
	}
}

void Lattice::print(void) {
	for (unsigned int i = 0; i < values.size(); i++) { 
		for(unsigned int j = 0; j < values[0].size(); j++) { 
			cout << values[i][j] << '\t'; 
		}
		cout << endl; 
	}
	cout << endl; 
}