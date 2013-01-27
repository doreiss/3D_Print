#include "Lattice.h"
#include "LatElem.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std; 

//Emprt constructor (default)
Lattice::Lattice(void){
}

//Constructor to create a lattice with a given number of rows, columns and starting value
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

//Constructor to  create a lattice based upon a file with values
Lattice::Lattice(char* file) {
	ifstream ifs(file);
	int fileVal; //value from the file
	string line;
	while(std::getline(ifs,line)) { //take the first line of the file
		std::istringstream iss(line); //make a stream out of the string
		vector<LatElem> row;
		while(iss >> fileVal) {
			LatElem elem; //create a lattice element from that individual point
			elem.setValue(fileVal); 
			row.push_back(elem);
		}
		values.push_back(row);
	}
	setElementNeighbours(); 
}

//Update all lattice element neighbour pointers
void Lattice::setElementNeighbours(void) { 
	//return lattice size
	int rows = rowSize(); 
	int cols = colSize(); 
	
	for(int rowIndex = 0; rowIndex < rows; rowIndex++) { 
		for(int colIndex = 0; colIndex < cols; colIndex++) {
			//is it on a boundary?
			bool isFirstRow = (rowIndex == 0);
			bool isFirstCol = (colIndex == 0); 
			bool isFinalRow = ((rowIndex + 1) == rows);
			bool isFinalCol = ((colIndex + 1) == cols);
			LatElem* current = &(values[rowIndex][colIndex]); //pointer to the current element in the lattice
			
			//functions to set pointers, with exceptions for boundaries
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

//Inset a sub-lattice into the system
void Lattice::insertSubLattice(Lattice L, int topLeftRow, int topLeftCol) {
	for (int i = 0; i < L.rowSize(); i++) { 
		for (int j = 0; j < L.colSize(); j++) { 
			setElement(topLeftRow+i, topLeftCol+j, L.getElemVal(i,j)); 
		} 
	} 
}


//Set the value of a lattice element
void Lattice::setElement(int rowInd, int colInd, int init) {
	values[rowInd][colInd].setValue(init); 
}

//Return the value of a lattice element
int	Lattice::getElemVal(int rowInd, int colInd) {
	return values[rowInd][colInd].getValue(); 
}

//Get the whole lattice element object
LatElem Lattice::getElement(int rowInd, int colInd) {
	return values[rowInd][colInd];
}

//Get the height of a lattice - double check?
int Lattice::rowSize(void) { 
	return values.size(); 
}

//Get the width of a lattice
int Lattice::colSize(void) { 
	return values[0].size(); 
}

//Is a specific cell in the lattice occupied?
bool Lattice::isEmpty(int rowInd, int colInd) { 
	return (getElemVal(rowInd,colInd) == 0);
}

//Create a sub lattice
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

//Prints the lattice
void Lattice::print(void) {
	for (unsigned int i = 0; i < values.size(); i++) { 
		for(unsigned int j = 0; j < values[0].size(); j++) { 
			cout << getElemVal(i,j) << '\t'; 
		}
		cout << endl; 
	}
	cout << endl; 
}
