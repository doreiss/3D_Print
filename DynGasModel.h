#pragma once
#include "Model.h"

class DynGasModel : public Model {
public:
	//Constructors
	DynGasModel() : Model() {}
	DynGasModel(Lattice& l) : Model(l) {
		state->updateForces('d');
	}

	//Iterate method for the dynamic gas model
	void iterate(void) {
		for(int i = 0; i < state->rowSize(); ++i) { 
			for(int j = 0; j < state->colSize(); ++j) { //look at /all/ cells
				LatElem* elem = state->getElement(i,j);  //get the element where iterator is
				int entering = 0; //number of particles wanting to enter the cell
				vector<bool> is_empty;
				for (int k = 0; k < 8; ++k) {
					entering = 0;
					LatElem* neighbour = elem->getNeighbour(k);
					if(neighbour != NULL) {
						bool empty_test = neighbour->isEmpty();
						is_empty.push_back(empty_test);			
						if (!(empty_test)) { //is the neighbour empty? if so let the cell know
							int force_dir = neighbour->getForceDir();
							//count the number of neighbour wanting to enter the cell
							if (k <= 3 && force_dir == (k-4)) {
								++entering;
							}
							else if (k > 3 && force_dir == (k-4)) {
								++entering;
							}
						}

					}
					else {
						is_empty.push_back(false);
					}
				}
				is_empty.push_back(elem->isEmpty()); //is the centre cell empty?
				/* Up to here is fine. We then know:
					What particles are full around the cell incl cell itself
					What particles want to enter the cell
				*/
				cout << elem->getForceX() << " " << elem->getForceY() << '\n';
				if(is_empty[8]) { //if there is no particle here
					if (entering > 1) { //more than one particle wants to enter
						for (int k = 0; k < 8; ++k) {
							if(!(is_empty[k])) { //reflect all the particles around the box
								LatElem* neighbour2 = elem->getNeighbour(k);
								int new_force_x = neighbour2->getForceX();
								int new_force_y = neighbour2->getForceY();
								new_force_x *= -1;
								new_force_y *= -1;
								neighbour2->setForce(new_force_x,new_force_y);
							}
						}
					} 
					else if (entering == 1) { //exactly one particle wants to enter
						for (int k = 0; k < 8; ++k) {
							if(!(is_empty[k])) { //carry forces over
								elem->setValue(elem->getNValue(k));
								elem->setForce(elem->getNForceX(k),elem->getNForceY(k));
								elem->makeNEmpty(k);
							}
						}
					}
				}
				else { //Look at the occupied cells around the particle and update force accordingly#
					bool all_N_empty = true;
					for (int k = 0; k < 8; ++k) {
						if(!(is_empty[k])) {
							all_N_empty = false;
							LatElem* neighbour2 = elem->getNeighbour(k);
							if (neighbour2 != NULL) {
								int new_force_x = neighbour2->getForceX();
								int new_force_y = neighbour2->getForceY();
								new_force_x *= -1;
								new_force_y *= -1;
								neighbour2->setForce(new_force_x,new_force_y);
							}
						}
					}
					if(!(all_N_empty)) {
						elem->setForce('d');
					}
				}
			}
		}
		Lattice save = *state; 
		system_states.addLattice(save);
	}

	void iterate(int n) { 
		for(int i = 0; i < n; i++) {
			cout << (i + 1) << '\n';
			//state->print();
			iterate(); 
		}
	}
} ;