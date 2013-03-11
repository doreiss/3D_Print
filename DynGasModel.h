#pragma once
#include <algorithm>
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
		//Lattice dimensions
		int numRows = state->rowSize();
		int numCols = state->colSize();
		//Are the cells around empty?
		vector<bool> is_empty_base (numCols+2,false);
		vector<vector<bool>> is_empty (numRows+2,is_empty_base);
		//Are the cells around a point entering?
		vector<bool> entering_base (8,false);
		vector<vector<bool>> entering_base2 (numCols+2,entering_base);
		vector<vector<vector<bool>>> entering (numRows+2,entering_base2);
		//How many cells want to enter?
		vector<int> num_entering_base (numCols+2,0);
		vector<vector<int>> num_entering (numRows+2,num_entering_base);
		//First loop
		for(int j = 1; j <= numRows; ++j) { 
			for(int i = 1; i <= numCols; ++i) { //look at /all/ cells
				LatElem* elem = state->getElement(i,j);  //get the element where iterator is
				//cout << elem->getForceX() << "," << elem->getForceY() << "\t";
				if(elem->isEmpty()) {
					is_empty[i][j] = true;
				}
				for(int k = 0; k < 8; ++k) {
					if(elem->getNValue(k) == LatElem::LatType::Full) {
						int force_dir= elem->getNForceDir(k);
						if (k < 4) {
							if ((force_dir-4) == k) {
								entering[i][j][k] = true;
								num_entering[i][j] += 1;
							}
						}
						else {
							if ((k-4) == force_dir) {
								entering[i][j][k] = true;
								num_entering[i][j] += 1;
							}
						}
					}
				}
			}
			//cout << '\n';
		}
		/* We then know:
			If particle empty:
				-Is more than one particle wanting to enter? If so reflect them.
				-If not, then move the new particle inside
			If particle full:
				-Does a particle want to enter? If so reflect it
				-Make the center particle move change direction
		*/
		//Second loop
		for(int j = 1; j <= numRows; ++j) { 
			for(int i = 1; i <= numCols; ++i) { //look at /all/ cells
				LatElem* elem = state->getElement(i,j);
				if(is_empty[i][j]) { //if there is no particle here
					for(int k = 0; k < 8; ++k) {
						if (entering[i][j][k]) {
							int newNForce_x = elem->getNForceX(k);
							int newNForce_y = elem->getNForceY(k);
							if (num_entering[i][j] == 1) {
								elem->setForce(newNForce_x,newNForce_y);
								elem->setValue(LatElem::LatType::Full);
								elem->makeNEmpty(k);
							}
							else if (num_entering[i][j] > 1) {
								newNForce_x *= -1;
								newNForce_y *= -1;
								elem->setNForce(k,newNForce_x,newNForce_y);
							}
						}
					}
				}
				else {
					int newForce_x = 0;
					int newForce_y = 0;
					bool change_x = false;
					bool change_y = false;
					for(int k = 0; k < 8; ++k) {
						if (entering[i][j][k]) {
							int newNForce_x = elem->getNForceX(k);
							int newNForce_y = elem->getNForceY(k);
							newNForce_x *= -1;
							newNForce_y *= -1;
							elem->setNForce(k,newNForce_x,newNForce_y);
							switch (k) {
							case 0:
								newForce_x -= 1;
								change_x = true;
								break;
							case 1:
								newForce_x -= 1;
								newForce_y -= 1;
								change_x = true;
								change_y = true;
							case 2:
								newForce_y -= 1;
								change_y = true;
								break;
							case 3:
								newForce_x += 1;
								newForce_y -= 1;
								change_x = true;
								change_y = true;
								break;
							case 4:
								newForce_x += 1;
								change_x = true;
								break;
							case 5:
								newForce_x += 1;
								newForce_y += 1;
								change_x = true;
								change_y = true;
								break;
							case 6:
								newForce_y += 1;
								change_y = true;
								break;
							case 7:
								newForce_x -= 1;
								newForce_y += 1;
								change_x = true;
								change_y = true;
								break;
							default:
								cout << "Something has broken, check syntax!\n";
							}
						}
					}
					if (change_x) {
						if(newForce_x > 1) {
							newForce_x = 1;
						}
						else if(newForce_x < 1) {
							newForce_x = -1;
						}
						elem->setForce(newForce_x,elem->getForceX());
					}
					if (change_y) {								
						if(newForce_y > 1) {
							newForce_x = 1;
						}
						else if(newForce_y < 1) {
							newForce_x = -1;
						}
						elem->setForce(elem->getForceY(),newForce_y);
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