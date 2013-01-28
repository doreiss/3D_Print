#include "Gas.h"
#include "Lattice.h"
#include "LatElem.h"
#include "LatElemUpdate.h"
#include <cmath> 
#include <vector> 

using namespace std;

Gas::Gas(void) { //default empty constructor
}

Gas::Gas(Lattice initial) { //default constructor for a given lattice object
	state = initial;
}

void Gas::iterate(void) {
	state.updateForces(); 
	//Lattice state_copy = state;
	for(int i = 0; i < state.rowSize(); i++) { 
		for(int j = 0; j < state.colSize(); j++) { 
			LatElem elem = state.getElement(i,j); 
			if(elem.getValue() == 0) { 
				vector < int > valid_dir; 
				vector < int > valid_mag; 

				for(int k = 0; k < 8; k++) { 
					if(elem.getNValue(k) == 1) {
						if(elem.getNForce(k).getForceDir() == (k+4)%7) {
							valid_dir.push_back(k); 
							valid_mag.push_back(elem.getNForce(k).getForceMag()); 
						}
					}
				}
			
				if(valid_dir.size() == 1) { 
					state.setElement(i,j,1); 
					state.setElement(i+convertDirX(valid_dir[0]),j+convertDirY(valid_dir[0]),0);
				}
			}
		}
	}
	//state = state_copy; 
}

void Gas::print(void) { 
	state.print(); 
}
