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
Lattice::Lattice(char* file,bool ishuman) {
	if(ishuman) {
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
	else {
		cout << "This doesn't exist yet, bug Josh to fix it!\n";
		//my version goes here
	}
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

//Updates the forces throughout the Lattice
void Lattice::updateForces(void) { 
	for(int i = 0; i < rowSize(); i++) { 
		for(int j = 0; j < colSize(); j++) { 
			values[i][j].setForce();
		}
	}
}


//Set the value of a lattice element
void Lattice::setElement(int rowInd, int colInd, int init) {
	getElement(rowInd,colInd)->setValue(init); 
}

//Return the value of a lattice element
int	Lattice::getElemVal(int rowInd, int colInd) {
	return values[rowInd][colInd].getValue(); 
}

//Get the whole lattice element object
LatElem* Lattice::getElement(int rowInd, int colInd) {
	return &values[rowInd][colInd];
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

//Prints the lattice to cout
void Lattice::print(void) {
	for (unsigned int i = 0; i < values.size(); i++) { 
		for(unsigned int j = 0; j < values[0].size(); j++) { 
			cout << getElemVal(i,j) << '\t'; 
		}
		cout << endl; 
	}
	cout << endl; 
}

//Print the lattice to a file (initial version)
void Lattice::fileprint(bool filetype){
	ofstream outfile;
	int rows = Lattice::rowSize();
	int cols = Lattice::colSize();
	if (filetype) {
		outfile.open("latticeview.txt");
		for (int j = 0; j < rows; ++j) {
			for (int i = 0; i < cols; ++i) {
				outfile << Lattice::getElemVal(i, j);
				if (i != (cols - 1)) { //are we at the end of the row?
					outfile << '\t';
				}
				else {
					outfile << '\n';
				}
			}
		}
	}
	else {
		outfile.open("lattice.flow",ios::app); //ios:app opens the file in append mode
		/* How this file works:
		For a lattice of size n x n, element Li,j
		Each line in the file:
		x	y	L1,1  ...	L1,n   L2,1	 ...	L2,n   ...	Ln,1  ...	Ln,n NEWLINE
		etc	*/

		outfile << cols << '\t' << rows << '\t';
		for (int j = 0; j < rows; ++j) {
			for (int i = 0; i < cols; ++i) {
				outfile << Lattice::getElemVal(i, j) << '\t';
			}
		}
		outfile << '\n';
	}
	outfile.close();
}

/*
//Print the lattice to a file (include time)
void Lattice::fileprint(int time){
}
*/

/*
void Lattice::fileread(&ofstream){
}
*/

//Find the maximum value in a vector of ints
int findMax(vector<int> v) { 
	int max = 0; 
	for(unsigned int i = 0; i < v.size(); i++) {
		if(max < v.at(i)) { 
			max = v.at(i);
		}
	}
	return max;
}

//Convert an integer direction ("Jensen Notation") into a unit cartesian x value
int convertDirX(int dir) { 
	int x = 0; 
	if (dir == 2 || dir == 6 || dir == 8) x = 0;
	else if (dir == 0 || dir == 1 || dir == 7) x = 1;
	else if (dir == 3 || dir == 4 || dir == 5) x = -1;
	return x; 
}

//Convert an integer direction ("Jensen Notation") into a unit cartesian y value
int convertDirY(int dir) { 
	int y = 0; 
	if (dir == 0 || dir == 4 || dir == 8) y = 0;
	else if (dir == 1 || dir == 2 || dir == 3) y = 1;
	else if (dir == 5 || dir == 6 || dir == 7) y = -1;
	return y; 
}
