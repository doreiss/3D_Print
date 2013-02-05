#include "Lattice.h"
#include "LatElem.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
using namespace std; 

//Empty constructor (default)
Lattice::Lattice(void){
}

//Constructor to create a lattice with a given number of rows, columns and starting value
Lattice::Lattice(int rows, int columns, LatElem::LatType init) {
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
Lattice::Lattice(string filename, bool ishuman, int line) {
	ifstream infile;
	string input;
	if(ishuman) {
		input.assign(filename.end()-4,filename.end()); //check filename to see if extension given
		if (input != ".txt") {
			filename.append(".txt");
		}
		infile.open(filename); //open the file
		int fileVal; //value from the file
		while(getline(infile,input)) { //take the first line of the file
			istringstream iss(input); //make a stream out of the string
			vector<LatElem> row;
			while(iss >> fileVal) {
				LatElem elem; //create a lattice element from that individual point
				LatElem::LatType newVal = (fileVal == 0 ? LatElem::Empty : LatElem::Full); 
				elem.setValue(newVal); 
				row.push_back(elem);
			}
			values.push_back(row);
		}
	}
	else {
		/*input.assign(filename.end()-4,filename.end()); //check filename to see if extension given
		if (input != ".flow") {
			filename.append(".flow");
		}*/
		infile.open(filename); //open relevant stream
		//check to make sure we aren't reading from a nonexistant line in the flow file
		int filelength = fileLines(infile); //fileLines function takes into account first line with information
		//cout << filelength;
		if (line > filelength) {
			line = filelength; //
			cout << "Warning! Supplied line number too large. Using last line of .flow file";
		}
		else if (line <= 0) {
			line = 1; //
			cout << "Warning! Supplied line number too small. Using first line of .flow file";
		}
		//cout << line;
		infile.seekg(ios::beg); //reset stream position
		getline(infile,input,'\t'); //take the first line in the file
		int cols = atoi(input.c_str()); //number of columns (x direction)
		//cout << cols;
		getline(infile,input,'\t');
		int rows = atoi(input.c_str()); //number of rows (y direction)
		infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for(int i = 1; i < line; ++i) { //move stream to required position
			infile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		//Now we can start to read from the file
		for(int i = 0; i < rows; ++i) {
			vector<LatElem> row; 
			for(int j = 0; j < cols; ++j) {
				getline(infile,input,'\t');
				int fileVal = atoi(input.c_str());
				LatElem elem;
				LatElem::LatType newVal = (fileVal == 0 ? LatElem::Empty : LatElem::Full); 
				elem.setValue (newVal);
				row.push_back(elem);
			}
			values.push_back(row);
		}
	}
	infile.close();
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
	/*	sub-lattice to be inserted, top left row position, top right row position
		corresponds to point of insertion */
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
void Lattice::setElement(int rowInd, int colInd, LatElem::LatType init) {
	getElement(rowInd,colInd)->setValue(init); 
}

//Return the value of a lattice element
LatElem::LatType Lattice::getElemVal(int rowInd, int colInd) {
	return values[rowInd][colInd].getValue(); 
}

//Get the whole lattice element object
LatElem* Lattice::getElement(int rowInd, int colInd) {
	return &values[rowInd][colInd];
}

//Get the height of a lattice
int Lattice::rowSize(void) { 
	return values.size(); 
}

//Get the width of a lattice
int Lattice::colSize(void) { 
	return values[0].size(); 
}

//Is a specific cell in the lattice occupied?
bool Lattice::isEmpty(int rowInd, int colInd) { 
	return (getElemVal(rowInd,colInd) == LatElem::Empty);
}

//Create a sub lattice
void Lattice::setSubLattice(int bRowInd, int eRowInd, int bColInd, int eColInd, LatElem::LatType init) {
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
	for (int i = 0; i < rowSize(); i++) { 
		for(int j = 0; j < colSize(); j++) { 
			cout << getElemVal(i,j) << '\t'; 
		}
		cout << endl; 
	}
	cout << endl; 
}

//Print the lattice to a file (initial version)
/* Usage
filetype: true - output .txt file (human use, single step only)
		  false - output .flow file (computer file, saves multiple steps)
newfile: is this a new file? (.flow files only)
step: .txt files - step number
	  .flow files - time between successive steps (default 1)
*/
void Lattice::filePrint(bool filetype,bool newfile,int step){
	ofstream outfile;
	int rows = Lattice::rowSize();
	int cols = Lattice::colSize();
	if (filetype) { //move this to a function
		outfile.open("latticeview.txt");
		outfile << "Lattice size: " << cols << " x " << rows << "\tStep number: " << step << '\n';
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
		/* How this "computer readable" file works:
		For a lattice size: N x M, elements: Li,j, time between steps: step
		First line: N \t M \t t
		Successive lines:
		x	y	L1,1  ...	L1,n   L2,1	 ...	L2,n   ...	Ln,1  ...	Ln,n NEWLINE
		etc	*/
		if(newfile) { //overwrite and create a new file
			outfile.open("lattice.flow");
			outfile << cols << '\t' << rows << '\t' << step << '\n';
		} 
		else { //append to an existing file
			outfile.open("lattice.flow",ios::app);
		} 
		for (int j = 0; j < rows; ++j) {
			for (int i = 0; i < cols; ++i) {
				outfile << Lattice::getElemVal(j, i) << '\t';
				//print the element force, requires a complete reworking of the way we handle force
			}
		}
		outfile << '\n';
	}
	outfile.close();
}

//As above, but assume step size = 1
void Lattice::filePrint(bool ishuman,bool newfile) {
	Lattice::filePrint(ishuman,newfile,1);
}

//Read a given line from lattice.flow file
void Lattice::fileRead(int line) {
	Lattice::fileRead("lattice",line);
}

//Read a given line from filename.flow file //This isn't implemented ! - Dom
void Lattice::fileRead(string,int) {
	
	;
}

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

/*
Functions useful when using .flow files
1st: Open a new stream of lattice.flow and return no. of lines
2nd: Open a new stream of filename.flow and return no. of lines
3rd: For an already open stream return no. of lines
*/

//Check the number of useful lines in Lattice.flow
int fileLines(void) {
	int lines = fileLines("Lattice");
	return lines;
}

//Check the number of useful lines in filename.flow
int fileLines(string filename) {
	filename.append(".flow");
	ifstream infile;
	infile.open(filename);
	int lines = fileLines(infile);
	infile.close();
	return lines;
}

//Check the number of useful lines for a file already open in a given stream
int fileLines(ifstream& infile) {
	infile.seekg(ios::beg); //reset stream position to beginning of file
	int lines = (int)count( //this a function in <algorithm> designed specifically for counting
			istreambuf_iterator<char>(infile),
			istreambuf_iterator<char>(),'\n');
	--lines;
	return lines;
}