#include "Flow.h"
#include "LatElem.h"
#include "Lattice.h"
#include <fstream>

using namespace std;

//default empty constructor
Flow::Flow(void) {
	cout << "Warning, empty constructor called!\n";
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

/*
//From a file
Flow::Flow(string filename) {
}
*/

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
bool Flow::checkLatticeSize(Lattice testlattice) {
	bool test = false;
	if (testlattice.rowSize() == Flow::getRows()) {
		if(testlattice.colSize() == Flow::getCols()) {
			test = true;
		}
		else {
			cout << "Column size inequal.\n";
		}
	}
	else {
		cout << "Row size inequal.\n";
	}
	return test;
}

//Return the number of total lattice states in the vector
int Flow::numStates(void) {
	int states;
	if(Flow::isEmpty()) {
		states = 0;
	}
	else {
		states = system.size();
	}
	return states;
}

//Add a lattice to end of the file
void Flow::addLattice(Lattice current_state) {
	if (Flow::checkLatticeSize(current_state)) {
		system.push_back(current_state);
	}
	else {
		checkSyntax();
	}
} //this works fine for empty vectors, apparently

//Add a lattice after a given line number (0 for beginning)
void Flow::addLattice(Lattice current_state, int step) {
	if(Flow::isEmpty()) {system.push_back(current_state);}


	/*
	int size = system.size(); //avoids signed/unsigned warnings
	if (step < 0) {
		step = 0;
		cout << "Warning! Check your syntax on where you are inserting your lattice into the flow object!\n";
	} //allow values of step <0, but give a warning message: it makes no sense to insert at an element < 0
	else if (step >= size) {
		step = system.size();
		step -= 1;
		cout << "Warning! Check your syntax on where you are inserting your lattice into the flow object!\n";
	} //allow values of step > vector size, but give a warning message: you should keep track of how big the vector is
	//vector iterator defining where the lattice needs to be inserted
	vector<Lattice>::iterator it = system.begin()+step;  
	system.insert(it,current_state);
	*/
}

//Return a lattice object at a given time
Lattice Flow::readLattice(int value) {
	if (system.size() == 0) {
		Lattice empty;
		cout << "Flow has no Lattice members stored, returning empty lattice! ";
		checkSyntax();
		return empty;
	}
	else {
		return system[value];
	}
}

//Returtn the last lattice object in the flow
Lattice Flow::readLattice(void) {
	int size = system.size();
	size -= 1;
	Lattice toreturn = Flow::readLattice(size);
	return toreturn;
}


//Cout last lattice state
void Flow::print(void) {
	int laststate = system.size();
	Flow::print(laststate);
}


//Cout a specific lattice state
void Flow::print(int timestep) {
	timestep -= 1;
	if (timestep >= (int)system.size()) {
		cout << "Warning, requested timestep outside of range, printing last step instead. ";
		checkSyntax();
		timestep = system.size();
		timestep--;
	}
	else if (timestep < 0) {
		cout << "Warning, requested timestep outside of range, printing first step instead. ";
		checkSyntax();
		timestep = 0;
	}
	if (system.size() == 0) {
		cout << "No lattices stored in flow object, nothing to print! ";
		checkSyntax();
	}
	else {
		Lattice toprint = system[timestep];
		toprint.print();
	}
}


//Print information to lattice.flow
void Flow::filePrint(void) {
	Flow::filePrint("lattice.flow");
}

//Print information to filename.flow
void Flow::filePrint(string filename) {
	string input;
	input.assign(filename.end()-4,filename.end()); //check filename to see if extension given
		if (input != ".flow") {
			filename.append(".flow");
		}
	ofstream outfile;
	outfile.open(filename); //open the stream
	outfile << cols << '\t' << rows << '\n';
	for (unsigned int i = 0; i < system.size(); ++i) {
		Lattice toprint = Flow::readLattice(i);
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

void checkSyntax(void) {
	cout << "Check your Syntax!\n";
}