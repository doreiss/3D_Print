#include "Flow.h"
#include "LatElem.h"
#include "Lattice.h"
#include <fstream>

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

//Return the number of total lattice states in the vector
int Flow::numStates(void) {
	int states = system.size();
	return states;
}

//Add a lattice to end of the file
void Flow::addLattice(Lattice current_state) {
	system.push_back(current_state);
}

//Add a lattice after a given line number (0 for beginning)
void Flow::addLattice(Lattice current_state, int step) {
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
}

//Return a lattice object at a given time
Lattice Flow::readLattice(int value) {
	value -= 1;
	return system[value];
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
	Lattice toprint = system[timestep];
	toprint.print();
}


//Print information to .flow file
void Flow::filePrint(void) {

}