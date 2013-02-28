#pragma once
#include "Model.h"

class DynGasModel : public Model {
	//Constructors
	DynGasModel() : Model() {}
	DynGasModel(Lattice& l) : Model(l) {}

	//Iterate method for the dynamic gas model
	void iterate(void) {
		state->updateForces('d'); //Update the forces in each cell
		//cout << "here2" << endl; 
		for(int i = 0; i < state->rowSize(); ++i) { 
			for(int j = 0; j < state->colSize(); ++j) { //look at /all/ cells
				LatElem* elem = state->getElement(i,j);  //get the element where iterator is
				int entering = 0; //number of particles wanting to enter the cell
				vector<bool> is_empty;
				for (int k = 0; k < 8; ++k) {
					LatElem* neighbour = elem->getNeighbour(k);
					bool empty_test = neighbour->isEmpty();
					is_empty.push_back(empty_test);			
					if (!(empty_test)) {	
						int force_dir = neighbour->getForceDir();
						//count the number of neighbour wanting to enter the cell
						if (force_dir = (k+4) && k <= 3) {
							++entering;
						}
						else if (force_dir = (k-4) && k > 3) {
							++entering;
						}
					}
				}
				is_empty.push_back(elem->isEmpty()); //is the centre cell empty?
				if(is_empty[8]) {
					for (int k = 0; k < 8; ++k) {
						if (entering > 1) { //more than one particle wants to enter
							if(!(is_empty[k])) {
								LatElem* neighbour2 = elem->getNeighbour(k);
								int new_force_x = neighbour2->getForceX();
								int new_force_y = neighbour2->getForceY();
								new_force_x *= -1;
								new_force_y *= -1;
								neighbour2->setForce(new_force_x,new_force_y);
							}
						} 
						else if (entering == 1) { //exactly one particle wants to enter
							if(!(is_empty[k])) { //carry forces over
								elem->setValue(elem->getNValue(k));
								elem->setForce(elem->getNForceX(k),elem->getNForceY(k));
								elem->makeNEmpty(k);
							}
						}
					}
				}
				else { //Look at the occupied cells around the particle and update force accordingly
					for (int k = 0; k < 8; ++k) { 
						if(!(is_empty[k])) {
							//Stuff
						}
					}
				}
			}
		}

		Lattice save = *state; 
		system_states.addLattice(save);

	void iterate(int n) { 
		for(int i = 0; i < n; i++) { 
			iterate(); 
		}
	}
} ;