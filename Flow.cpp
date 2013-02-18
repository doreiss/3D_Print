#include "Flow.h"
#include "LatElem.h"
#include "Lattice.h"
#include <fstream>
#include <stdexcept>

using namespace std;

//default empty constructor
Flow::Flow(void) {
}

//Specify initial row, column
Flow::Flow(int row_s, int columns) {
	rows = row_s;
	cols = columns;
}

//From a single initial lattice
Flow::Flow(Lattice& state, bool firstrow) {
	cols = state.colSize();
	rows = state.rowSize();
	if(firstrow) { //if true 
		system.push_back(state);
	}
}

//From a file
Flow::Flow(string filename) {
	ifstream infile;
	string input;
	input.assign(filename.end()-4,filename.end()); //make sure filename ends in .flow
	if (input != ".flow") {
		filename.append(".flow");
	}
	//columns
	getline(infile,input,'\t');
	cols = atoi(input.c_str());
	//rows
	getline(infile,input,'\n');
	rows = atoi(input.c_str());
	infile.seekg(ios::beg);
	int lines = fileLines(filename);
	lines--;
	infile.close();
	//now comes for the horrible part
	for (int i = 0; i < lines; ++i) {
		Lattice(filename,false,i);
	}
}

//Return the column size of the flow file
int Flow::getCols(void) {
	return cols;
}

//Return the row size of the flow file
int Flow::getRows(void) {
	return rows;
}

//Return true if the system vector is empty, false if not
bool Flow::isEmpty(void) {
	return system.empty();
}

//Return true if Lattice size matches up with that dictated by flow file, false otherwise
void Flow::checkLatticeSize(Lattice testlattice) {
	if (testlattice.rowSize() != Flow::getRows()) {
		throw runtime_error("Row size inequal.\n");
	}
	if(testlattice.colSize() != Flow::getCols()) {
		throw runtime_error("Column size inequal.\n");
	}
}

//Does the system vector have a given lattice? (Eg, is there a lattice number 3 in the flow?)
void Flow::checkSystem(int step) {
	int systemsize = Flow::numStates();
	if (step < 0) {
		throw runtime_error("Timestep given less than zero.\n");
	}
	if (step >= systemsize) {
		throw runtime_error("Timestep given greater than system size.\n");
	}
}

//Return the number of total lattice states in the vector
int Flow::numStates(void) {
	return system.size();
}

//Add a lattice to end of the file
void Flow::addLattice(Lattice current_state) {
	try {
		Flow::checkLatticeSize(current_state);
		system.push_back(current_state);
	}
	catch (exception problem) {
		cout << problem.what();
	}
} //this works fine for empty vectors, apparently

//Add a lattice after a given line number (0 for beginning)
void Flow::addLattice(Lattice current_state, int step) {
	try {
		Flow::checkLatticeSize(current_state);
		Flow::checkSystem(step);
		vector<Lattice>::iterator it = system.begin() + step;
		system.insert(it,current_state);
	}
	catch (exception problem) {
		cout << problem.what();
	}
}

//Return a lattice object at a given time - Redo this
Lattice Flow::getLattice(int value) {
	Lattice toreturn;
	try {
		Flow::checkSystem(value);
		toreturn = system[value];
	}
	catch (exception problem) {
		cout << problem.what();
	}
	return toreturn;
}

//Returtn the last lattice object in the flow
Lattice Flow::getLattice(void) {
	int size = (system.size() - 1);
	Lattice toreturn = system[size];
	return toreturn;
}

//Cout last lattice state
void Flow::print(void) {
	int laststate = (system.size() - 1);
	Flow::print(laststate);
}

//Cout a specific lattice state
void Flow::print(int timestep) {
	Lattice toprint = Flow::getLattice(timestep);
	toprint.print();
}

//Print information to lattice.flow
void Flow::filePrint(void) {
	Flow::filePrint("lattice.flow");
}

//Print information to filename.flow
void Flow::filePrint(string filename) {
	string input;
	input.assign(filename.end()-4,filename.end()); //make sure filename ends in .flow
		if (input != ".flow") {
			filename.append(".flow");
		}
	ofstream outfile;
	outfile.open(filename); //open the stream
	outfile << cols << '\t' << rows << '\n';
	for (unsigned int i = 0; i < system.size(); ++i) {
		Lattice toprint = Flow::getLattice(i);
		//move this next function to lareadttice.cpp
		for (int j = 0; j < rows; ++j) {
			for (int k = 0; k < cols; ++k) {
				outfile << toprint.getElemVal(j,k) << '\t';
			}
		}
		outfile << '\n';	
	}
	outfile.close();
}