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
				for(int k = 0; k < 8; k++) {
					LatElem* neighbour = elem->getNeighbour(k);
					if(neighbour->getValue() == 1) { //Check if neighbour wants to enter elem ij
						if(neighbour->getForceDir() == (k+4)%8) {
							valid_dir.push_back(k); 
						}
					}
				}
				if(valid_dir.size() == 1) { //If approrpiate move the negihbour into the cell ij
					state->setElement(i,j,1);
					state->setElement(i-convertDirY(valid_dir[0]),j+convertDirX(valid_dir[0]),0);
				}
			}
		}
	}
}

void Gas::print(void) { 
	state->print(); 
}
