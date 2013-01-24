#include "Lattice.h"
#include "LatElem.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std; 

Lattice::Lattice(void){ 
}

Lattice::Lattice(int rows, int columns, int init) {
	for(int i = 0; i < rows; i++) {
		vector<LatElem> row; 
		for(int i = 0; i < columns; i++) {
			LatElem elem; 
			elem.setValue(init); 
			row.push_back(elem);
		}
		values.push_back(row); 
	}
	setElementNeighbours(); 
}

Lattice::Lattice(char* file) {
	ifstream ifs(file);
	int fileVal; 
	string line; 
	while(std::getline(ifs,line)) {
		std::istringstream iss(line);
		vector<LatElem> row;
		while(iss >> fileVal) {
			LatElem elem; 
			elem.setValue(fileVal); 
			row.push_back(elem);
		}
		values.push_back(row);
	}
	setElementNeighbours(); 
}

void Lattice::setElementNeighbours(void) { 
	int rows = rowSize(); 
	int cols = colSize(); 
	
	for(int rowIndex = 0; rowIndex < rows; rowIndex++) { 
		for(int colIndex = 0; colIndex < cols; colIndex++) {
			bool isFirstRow = (rowIndex == 0); 
			bool isFirstCol = (colIndex == 0); 
			bool isFinalRow = ((rowIndex + 1) == rows);
			bool isFinalCol = ((colIndex + 1) == cols);
			LatElem* current = &(values[rowIndex][colIndex]); 
			if (!isFinalCol)				current->setNeighbours(0,values[rowIndex][colIndex+1]);
			if (!isFirstRow && !isFinalCol) current->setNeighbours(1,values[rowIndex-1][colIndex+1]);
			if (!isFirstRow)				current->setNeighbours(2,values[rowIndex-1][colIndex]);
			if (!isFirstRow && !isFirstCol) current->setNeighbours(3,values[rowIndex-1][colIndex-1]);
			if (!isFirstCol)				current->setNeighbours(4,values[rowIndex][colIndex-1]);
			if (!isFirstCol && !isFinalRow)	current->setNeighbours(5,values[rowIndex+1][colIndex-1]);
			if (!isFinalRow)				current->setNeighbours(6,values[rowIndex+1][colIndex]);
			if (!isFinalRow && !isFinalCol)	current->setNeighbours(7,values[rowIndex+1][colIndex+1]);
		}
	}
}

void Lattice::setElement(int rowInd, int colInd, int init) {
	values[rowInd][colInd].setValue(init); 
}

int	Lattice::getElemVal(int rowInd, int colInd) {
	return values[rowInd][colInd].getValue(); 
}

LatElem Lattice::getElement(int rowInd, int colInd) {
	return values[rowInd][colInd];
}

int Lattice::rowSize(void) { 
	return values.size(); 
}

int Lattice::colSize(void) { 
	return values[0].size(); 
}

bool Lattice::isEmpty(int rowInd, int colInd) { 
	return (getElemVal(rowInd,colInd) == 0);
}

void Lattice::setSubLattice(int bRowInd, int eRowInd, int bColInd, int eColInd, int init) {
	int rows = 0, columns = 0; 
	columns = values.size(); 
	if (columns > 0) {
		rows = values[0].size();
	}
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
			cout << getElemVal(i,j) << '\t'; 
		}
		cout << endl; 
	}
	cout << endl; 
}
