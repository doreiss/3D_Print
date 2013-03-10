#pragma once
#include <algorithm>
#include <cstdlib>
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
		int numRows = state->rowSize();
		int numCols = state->colSize();
		for(int i = 0; i < numRows; ++i) { 
			for(int j = 0; j < numCols; ++j) { //look at /all/ cells
				LatElem* elem = state->getElement(i,j);  //get the element where iterator is
				//cout << elem->getForceX() << "," << elem->getForceY() << "\t";
				vector<bool> is_empty; //is the neighbour empty?
				vector<bool> entering; //is the neighbour wanting to enter the cell?
				for (int k = 0; k < 8; ++k) {
					LatElem* neighbour = elem->getNeighbour(k);
					if(neighbour != NULL) {
						bool empty_test = neighbour->isEmpty();
						is_empty.push_back(empty_test);			
						if (!(empty_test)) { //is the neighbour empty? if so let the cell know
							int force_dir = neighbour->getForceDir();
							//count the number of neighbour wanting to enter the cell
							if (k <= 3 && force_dir == (k+4)) {
								entering.push_back(true);
							}
							else if (k > 3 && force_dir == (k-4)) {
								entering.push_back(true);
							}
							else {
								entering.push_back(false);
							}
						}
						else {
							entering.push_back(false);
						}
					}
					else {
						is_empty.push_back(false);
						entering.push_back(false);
					}
				}
				is_empty.push_back(elem->isEmpty()); //is the centre cell empty?
				/* Up to here is fine. We then know:
					What particles are full around the cell incl cell itself
					What particles want to enter the cell
				*/
				cout << is_empty.size() << '\t' << entering.size() << '\n';
				system("Pause");
				int numEntering = count(entering.begin(),entering.end(),true); //number of trues in entering
				if(is_empty[8]) { //if there is no particle here
					if (numEntering > 1) { //more than one particle wants to enter
						for (int k = 0; k < 8; ++k) {
							if(is_empty[k] == false && entering[k] == true) { //reflect all the particles around the box
								int new_force_x = elem->getNForceX(k);
								int new_force_y = elem->getNForceY(k);
								new_force_x *= -1;
								new_force_y *= -1;
								elem->setNForce(k,new_force_x,new_force_y);
								//set the neighbour force
							}
						}
					} 
					else if (numEntering == 1) { //exactly one particle wants to enter
						for (int k = 0; k < 8; ++k) {
							if(is_empty[k] == false && entering[k] == true) { //carry forces over
								elem->setValue(elem->getNValue(k));
								elem->setForce(elem->getNForceX(k),elem->getNForceY(k));
								elem->makeNEmpty(k);
							}
						}
					}
				}
				else { //Look at the occupied cells around the particle and update force accordingly
					for (int k = 0; k < 8; ++k) {
						if(is_empty[k] == false && entering[k] == true) {
							LatElem* neighbour2 = elem->getNeighbour(k);
							if (neighbour2 != NULL) {
								int new_force_x = elem->getNForceX(k);
								int new_force_y = elem->getNForceY(k);
								new_force_x *= -1;
								new_force_y *= -1;
								elem->setNForce(k,new_force_x,new_force_y);
							}
						}
					}
				}
			}
			//cout << "\n";
		}
		Lattice save = *state; 
		system_states.addLattice(save);
	}

	void iterate(int n) { 
		for(int i = 0; i < n; i++) {
			cout << (i + 1) << '\n';
			state->print();
			iterate(); 
		}
	}
} ;