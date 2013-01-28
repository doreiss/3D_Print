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


//Updates State 1 Time Step
void Gas::iterate(void) {
	state->updateForces();
	for(int i = 0; i < state->rowSize(); i++) { 
		for(int j = 0; j < state->colSize(); j++) { 
			LatElem* elem = &(state->getElement(i,j));  
			if(elem->getValue() == 0) { 
				vector < int > valid_dir;
				for(int k = 0; k < 8; k++) {
					LatElem* neighbour = elem->getNeighbour(k);
					if(neighbour->getValue() == 1) {
						if(neighbour->getForceDir() == (k+4)%8) {
							valid_dir.push_back(k); 
						}
					}
				}
				if(valid_dir.size() == 1) { 
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
