#pragma once
#include <cstdlib>
#include "Model.h"
#include "ScreenClear.h"

void changeForces(int,int&,int&,bool&,bool&);
void makeEmptyK(vector<vector<bool>>&,int,int,int);
bool direction_test (int,int,int);

/* Because of something to do with dimensions, we have to use the following notation for some reason:

Considering coordinate z, position x,y, such that a neighbour k has the following directional value:

1 0 7
2 z 6
3 4 5

*/

class DynGasModel : public Model {
public:
	//Constructors
	DynGasModel() : Model() {}
	DynGasModel(Lattice& l) : Model(l) {
		//state->updateForces('d');
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
		vector<vector<bool>> entering_base2 (numCols,entering_base);
		vector<vector<vector<bool>>> entering (numRows,entering_base2);
		//How many cells want to enter?
		vector<int> num_entering_base (numCols,0);
		vector<vector<int>> num_entering (numRows,num_entering_base);
		//First loop
		for(int i = 0; i < numRows; ++i) { 
			for(int j = 0; j < numCols; ++j) { //look at /all/ cells
				LatElem* elem = state->getElement(i,j);  //get the element where iterator is
				if(elem->isEmpty()) { //is the cell empty? save this information
					is_empty[i+1][j+1] = true;
				}
				for(int k = 0; k < 8; ++k) { //for surrounded cells
					if(elem->getNValue(k) == LatElem::Full) { //if surrounded cell is full
						bool dirTest = direction_test(elem->getNForceX(k),elem->getNForceY(k),k);
						if(dirTest) { //if that cell wants to enter this cell
							entering[i][j][k] = true; //save this information
							cout << "Entering - " << i << " , " << j << " from " << k << '\n';
							num_entering[i][j] += 1; //note how many are entering
						}
					}
					else {
						entering[i][j][k] = false;
					}
				}
			}
		}
		/* We then know:
			Code above is fine.
			If particle empty:
				-Is more than one particle wanting to enter? If so reflect them.
				-If not, then move the new particle inside
			If particle full:
				-Does a particle want to enter? If so reflect it
				-Make the center particle move change direction
		*/
		//Second loop
		for(int i = 0; i < numRows; ++i) { 
			for(int j = 0; j < numCols; ++j) { //again look at all cells
				bool change_x = false; //is the force changing?
				bool change_y = false; //is the force changing?
				LatElem* elem = state->getElement(i,j); //look at a specific cell
				if (!(is_empty[i+1][j+1])) { //if the cell is full
					cout << "Full cell " << i << " , " << j
						 << " . F: " << elem->getForceX() << " , " << elem->getForceY() << '\n'; //print the force
					int newForce_x = elem->getForceX(); //get the force on that cell
					int newForce_y = elem->getForceY(); //based on the original force - conservation of momentum I guess?
					for(int k = 0; k < 8; ++k) { //look at neighbours
						if (entering[i][j][k]) { //is a particle trying to enter the cell? if so reflect it
							int newNForce_x = elem->getNForceX(k);
							int newNForce_y = elem->getNForceY(k);
							bool dirTest = direction_test(newNForce_x,newNForce_y,k);
							if (dirTest) { //check to make sure the force on the neighbour hasn't been updated by some other function
								newNForce_x *= -1;
								newNForce_y *= -1;
								elem->setNForce(k,newNForce_x,newNForce_y);
							}
							entering[i][j][k] = false;
							num_entering[i][j] -= 1;
							cout << "Full cell: " << i << " , " << j << " . Reflect: " << k << '\n';
						}
					}
					for(int k = 0; k < 8; ++k) { //is the cell around the particle full? if so update the force on the particle
						if(!(elem->isNEmpty(k))) {
							cout << "AFOC: " << i << " , " << j << " , " << k << "\t\t";
							changeForces(k,newForce_x,newForce_y,change_x,change_y);
							cout << newForce_x << " , " << newForce_y << '\n';
						}
					}
					//Are we changing the forces?
					if (change_x) {
						if(newForce_x >= 1) {
							newForce_x = 1;
						}
						else if(newForce_x <= 1) {
							newForce_x = -1;
						}
						else {
							newForce_x = 0;
						}
					}
					if (change_y) {
						if(newForce_y >= 1) {
							newForce_y = 1;
						}
						else if(newForce_y <= 1) {
							newForce_y = -1;
						}
						else {
							newForce_y = 0;
						}
					}
					//Set the forces now that they have been changed
					if (change_x && change_y) {
						elem->setForce(newForce_x,newForce_y);
					}
					else if (change_x && !(change_y)) {
						elem->setForce(newForce_x,elem->getForceY());
					}
					else if (!(change_x) && change_y) {
						elem->setForce(elem->getForceX(),newForce_y);
					}
					cout << "New F: " << elem->getForceX() << " , " << elem->getForceY() << '\n';	
				}
				else if(is_empty[i+1][j+1]) { //is there is no particle in a cell
					if(num_entering[i][j] > 1) {
						for(int k = 0; k < 8; ++k) {
							if(entering[i][j][k]) {
								int newNForce_x = elem->getNForceX(k); //get the force of that particle
								int newNForce_y = elem->getNForceY(k);
								bool dirTest = direction_test(newNForce_x,newNForce_y,k);
								if (dirTest) { //check to make sure the force on the neighbour hasn't been updated by some other function
									newNForce_x *= -1;
									newNForce_y *= -1;
									elem->setNForce(k,newNForce_x,newNForce_y);
								}
								entering[i][j][k] = false;
								num_entering[i][j] -= 1;
								cout << "Empty cell: " << i << " , " << j << " . RE @ " << k << '\n';
							}
						}
					}
					else if(num_entering[i][j] == 1) {
						for(int k = 0; k < 8; ++k) {
							if(entering[i][j][k]) {
								int newForce_x = elem->getNForceX(k);
								int newForce_y = elem->getNForceY(k);
								elem->setForce(newForce_x,newForce_y);
								elem->setValue(LatElem::LatType::Full);
								elem->makeNEmpty(k);
								makeEmptyK(is_empty,i+1,j+1,k);
								is_empty[i+1][j+1] = false;
								num_entering[i][j] -= 1;
								cout << "Moved pcle to: " << i << " , " << j << " from " << k << '\n';
							}
						}
					}
				}
			}
		}
		Lattice save = *state; 
		system_states.addLattice(save);
	}

	void iterate(int n) {
		cout << "0" << '\n';
		state->print();
		system("pause");
		system("cls");
		for(int i = 0; i < n; i++) {
			cout << (i + 1) << '\n';
			iterate();
			state->print();
			system("pause");
			system("cls");
		}
	}
} ;

void changeForces(int nIndex,int& newForce_x,int& newForce_y,bool& change_x,bool& change_y) {
	switch (nIndex) { //now adjust where the particle is going based on what cells around it are full
	case 0:
		newForce_y -= 1;
		change_y = true;
		break;
	case 1:
		newForce_y -= 1;
		newForce_x += 1;
		change_x = true;
		change_x = true;
		break;
	case 2:
		newForce_x += 1;
		change_x = true;
		break;
	case 3:
		newForce_x += 1;
		newForce_y += 1;
		change_x = true;
		change_y = true;
		break;
	case 4:
		newForce_y += 1;
		change_y = true;
		break;
	case 5:
		newForce_y += 1;
		newForce_x -= 1;
		change_y = true;
		change_x = true;
		break;
	case 6:
		newForce_x -= 1;
		change_x = true;
		break;
	case 7:
		newForce_x -= 1;
		newForce_y -= 1;
		change_x = true;
		change_y = true;
		break;
	default:
		cout << "Something has broken, check syntax!\n";
	}
}

void makeEmptyK(vector<vector<bool>>& is_empty,int i, int j,int nIndex) {
	switch(nIndex) {
	case 0:
		is_empty[i][(j+1)] = true;
		break;
	case 1:
		is_empty[(i-1)][(j+1)] = true;
		break;
	case 2:
		is_empty[(i-1)][j] = true;
		break;
	case 3:
		is_empty[(i-1)][(j-1)] = true;
		break;
	case 4:
		is_empty[i][(j-1)] = true;
		break;
	case 5:
		is_empty[(i+1)][(j-1)] = true;
		break;
	case 6:
		is_empty[(i+1)][j] = true;
		break;
	case 7:
		is_empty[(i+1)][(j+1)] = true;
		break;
	default:
		cout << "Something has broken, check syntax!\n";
	}
}

//For warped dimension (this is a hack to fix it)
bool direction_test (int x, int y, int nIndex) {
	bool toreturn = false;
	int other_jensen = convertXYDir(x,y);
	if (nIndex >= 2) {
		if(nIndex == (other_jensen + 2)) {
			toreturn = true;
		}
	}
	else {
		if(other_jensen == (nIndex + 6)) {
			toreturn = true;
		}
	}
	return toreturn;
}