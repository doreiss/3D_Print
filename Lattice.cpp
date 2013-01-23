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
	for(int i = 0; i < rows; i++) {
		row.push_back(init);
	}
	for(int i = 0; i < columns; i++) {
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
