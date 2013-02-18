#include "Gas.h"
#include "Lattice.h"
#include "LatElem.h"
#include "Flow.h"
#include <cmath> 
#include <vector> 

using namespace std;

//default empty constructor
Gas::Gas(void) { 
}

//default constructor for a given lattice object
Gas::Gas(Lattice& initial, Model type) { 
	system_type = type;
	state = &initial;
	Lattice save = *state; 
	Flow fsave(save,true);
	system_states = fsave;
}

//Return a pointer to a lattice of the current gas state
Lattice* Gas::getLattice(void) { 
	return state; 
}

//Updates State 1 Time Step
void Gas::iterate(void) {
	if(system_type = static_gas) {
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
							state->setElement(i,j,LatElem::Full);
							state->setElement(i-convertDirY(valid_dir[mmax]),j+convertDirX(valid_dir[mmax]),LatElem::Empty);
						}
					}
				}
			}
		}
		Lattice save = *state; 
		system_states.addLattice(save);
	}
	else if (system_type = forest_fire) {
		//update the forest
		for (int i = 0; i < state->rowSize(); ++i) {
			for (int j = 0; j < state->colSize(); ++j) {
				LatElem* elem = state->getElement(i,j);
				if (elem->isEmpty()) { //update only for "empty cells"
					bool update = false;
					for (int k = 0; k < 8; k++) { //look at neighbouring cells
						LatElem* neighbour = elem->getNeighbour(k);
						if (!(neighbour->isEmpty())) {
							update = true; //are any of the neighbouring cells occupied
						}
					}
					if(update) {
						int grow = random();
						int grow_prob = 10;
						grow_prob *= GROWTH;
						if (grow < grow_prob) {
							elem->setValue(LatElem::Full);
						}
					}
				}	
			}
		}
		//update which trees are being burnt
		for (int i = 0; i < state->rowSize(); ++i) {
			for (int j = 0; i <  state->colSize(); ++j) {
				int strike = random();
				int strike_prob = 10;
				strike_prob *= LIGHTNING_BASE;
				LatElem* elem = state->getElement(i,j);
				LatElem::LatType current_type = elem->getValue();
				if (current_type == LatElem::Burning) {
					int burn_time = elem->getBurnTime();
					burn_time--;
					if (burn_time == 0) {
						elem->setValue(LatElem::Empty);
					}
					elem->setBurnTime(burn_time);
				}
				if (strike < strike_prob) {
					if (current_type == LatElem::Full) {
						elem->setValue(LatElem::Burning);
						elem->setBurnTime(5);
					}
				}
				else if (current_type == LatElem::Full) {
					bool ignite = false;
					for (int k = 0; k < 8; ++k) {
						LatElem* neighbour = elem->getNeighbour(k);
						if(neighbour->getValue() == LatElem::Burning) {
							ignite = true;
						}
					}
					if(ignite) {
						int ignite_chance = random();
						int ignite_prob = 10;
						ignite_prob *= BURNING_SPREAD;
						if (ignite_chance < ignite_prob) {
							elem->setValue(LatElem::Burning);
							elem->setBurnTime(5);
						}
					}
				}
			}
		}
	}
}

//Updates State n times
void Gas::iterate(int n) { 
	for(int i = 0; i < n; i++) { 
		iterate(); 
	}
}

//Finds how many steps have been taken
int Gas::timeSize(void) { 
	return system_states.numStates(); 
}

//Prints the current state
void Gas::print(void) { 
	state->print(); 
}

//prints the current state to a file
void Gas::filePrint(bool ishuman) {
	state->filePrint(ishuman,false);
}

//prints the entire flow object to a file
void Gas::filePrintAll(void) {
	Lattice toprint;
	for (int i = 0; i < system_states.numStates(); ++i) {
		toprint = system_states.readLattice(i); //get a specific element
		if (i == 0) { //print this specific element
			toprint.filePrint(false,true);
		}
		else {
			toprint.filePrint(false,false); 
		}
	} //may be possible to redo this with pointers. only useful if we need to manage memory more
}

//Gets Lattice at time t from flow vector
Lattice Gas::getLatT(int t) { 
	return system_states.readLattice(t); 
}

//RNG from 0 -> 999
int random(void) {
	int number = rand() % 1000;
	return number;
}