#include "Gas.h"
#include "Lattice.h"
#include "LatElem.h"
#include <cmath> 
#include <vector> 

using namespace std;

Gas::Gas(void) { //default empty constructor
}

Gas::Gas(Lattice& initial) { //default constructor for a given lattice object
	state = &initial;
	Lattice save = *state; 
	flow.push_back(save); 
}
Lattice* Gas::getLattice(void) { 
	return state; 
}

//Updates State 1 Time Step
void Gas::iterate(void) {
	state->updateForces(); //Update the forces in each cell
	for(int i = 0; i < state->rowSize(); i++) { 
		for(int j = 0; j < state->colSize(); j++) { 
			LatElem* elem = state->getElement(i,j);  //get the element where iterator is
			if(elem->getValue() == 0) { //Only look at empty cells
				vector < int > valid_dir; //Stores the valid directions of incoming cells
				vector < double > valid_mag; //Stores the corresponding magnitudes of incoming cells
				for(int k = 0; k < 8; k++) {
					LatElem* neighbour = elem->getNeighbour(k);
					if(neighbour->getValue() == 1) { //Check if neighbour wants to enter elem ij
						if(neighbour->getForceDir() == (k+4)%8) {
							valid_dir.push_back(k); 
							valid_mag.push_back(neighbour->getForceMag()); 
						}
					}
				}
				//Check which neighbour gets to enter the cell
				if(valid_dir.size() >= 1) {
					double fmax = -1.0;
					int mmax = -1; 
					for(unsigned int n = 0; n < valid_dir.size(); n++) {
						if(valid_mag[n] >= fmax) { 
							fmax = valid_mag[n];
							mmax = n;
						}
					}
					//Check that there is only 1 maximum
					int counter = 0;
					for(unsigned int n = 0; n < valid_dir.size(); n++) {
						if(abs(valid_mag[n]-valid_mag[mmax]) < 0.00001) {
							counter++;
						}
					}
					if(counter == 1) { 
						state->setElement(i,j,1);
						state->setElement(i-convertDirY(valid_dir[mmax]),j+convertDirX(valid_dir[mmax]),0);
					}
				}
			}
		}
	}
	Lattice save = *state; 
	flow.push_back(save); 
}

//Finds how many steps have been taken
int Gas::timeSize(void) { 
	return flow.size(); 
}

//prints the current state
void Gas::print(void) { 
	state->print(); 
}

//prints the current state to a file
void Gas::filePrint(bool ishuman) {
	state->filePrint(ishuman);
}

//prints the entire flow object to a file
void Gas::filePrintAll(void) {
	Lattice toprint;
	for (unsigned int i = 0; i < flow.size(); ++i) {
		toprint = flow.at(i); //get a specific element
		toprint.filePrint(false); //print this specific element
	} //may be possible to redo this with pointers. only useful if we need to manage memory more
}

//Gets Lattice at time t
Lattice Gas::getLatT(int t) { 
	return flow[t]; 
}
