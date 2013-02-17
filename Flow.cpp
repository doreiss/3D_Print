#include "Flow.h"
#include "LatElem.h"
#include "Lattice.h"
#include <fstream>
#include <stdexcept>

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
	if (systemsize != 0) {
		systemsize--;
	}
	if (step < 0) {
		throw runtime_error("Timestep given less than zero.\n");
	}
	else if (step > systemsize) {
		throw runtime_error("Timestep given greater than system size.\n");
	}
}

//Return the number of total lattice states in the vector
int Flow::numStates(void) {
	return system.size();
}

//Add a lattice to end of the file - Redo this
void Flow::addLattice(Lattice current_state) {
	try {
		Flow::checkLatticeSize(current_state);
		system.push_back(current_state);
	}
	catch (exception problem) {
		cout << problem.what();
	}
} //this works fine for empty vectors, apparently

//Add a lattice after a given line number (0 for beginning) - Redo this
void Flow::addLattice(Lattice current_state, int step) {
	/*
	try { //testing exceptions, this is drawn out but is an example case
		Flow::checkLatticeSize(current_state);
	}
	catch (exception mistake) {
		cout << mistake.what();
	}
	if(Flow::checkLatticeSize(current_state))
	{
		int systemsize = Flow::numStates();
		vector<Lattice>::iterator it;
		if (systemsize != 0) {
			systemsize -= 1;
		} //allows the check of step to function correctly for all cases
		if(step < 0) {
			it = system.begin();
			system.insert(it,current_state);
			cout << "Trying to add Lattice at a negative step. Adding at beginning.\n";
		} //Allow values of step < 0, but give a warning
		else if(step > systemsize) {
			system.push_back(current_state);
			cout << "Trying to add Lattice at a step with too high a value. Adding lattice to end.\n";
		} //Allow values of step too big, but give a warning
		else {
			it = system.begin() + step;
			system.insert(it,current_state);
		}
	}
	*/
}

//Return a lattice object at a given time - Redo this
Lattice Flow::readLattice(int value) {

/* REDO WITH EXCEPTION HANDLING
	int states = Flow::numStates();
	if (states == 0) {
		Lattice empty;
		cout << "Requested Lattice from a step with too high a value. Returning last step.";
	}
	else if (value > states) {
		cout << "Requested Lattice from a step with too high a value. Returning last step.";
	}
	else if (value < 0) {

	}
		return system[value];
	}
*/
	return Lattice(10,10,LatElem::Full);
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
		timestep = system.size();
		timestep--;
	}
	else if (timestep < 0) {
		cout << "Warning, requested timestep outside of range, printing first step instead. ";
		timestep = 0;
	}
	if (system.size() == 0) {
		cout << "No lattices stored in flow object, nothing to print! ";
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