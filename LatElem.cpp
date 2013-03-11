#include "LatElem.h"
#include <iostream>
#include <cmath>

using namespace std; 

//Lattice element constructor with integer value
LatElem::LatElem(LatType init) {
	value = init;
	burn_time = 0;
	force_x = 0;
	force_y = 0;
	setNullNeighbours(); 
}

//Change the value of a lattice element to given integer value
void LatElem::setValue(LatType init) {
	value = init;
}

//Calculates the force on a given element, given its surrounding elements
void LatElem::setForce(char model_type) {
	if (model_type == 'g' || model_type == 'd' || model_type == 's') {
		if (value == LatElem::Empty) {
			force_x = 0;
			force_y = 0;
		}
		else if (model_type == 'g' || model_type == 's') {
			force_x = getNValue(4) - getNValue(0); 
			force_y = getNValue(6) - getNValue(2);
			if (model_type == 's') { //Strongest side wins - leaving in incase useful
				//Now look at diagonal forces too for the diagonal gas case
				int topl = getNValue(3);
				int topr = getNValue(1);
				int botl = getNValue(5);
				int botr = getNValue(7);
				force_x += (topl + botl);
				force_x -= (topr + botr);
				force_y += (botr + botl);
				force_y -= (topr + topl);
				//'Normalise' the size of the forces
				if (force_x > 0) {
					force_x = 1;
				}
				else if (force_x < 0) {
					force_x = -1;
				}
				if (force_y > 0) {
					force_y = 1;
				}
				else if (force_y < 0) {
					force_y = -1;
				}
			}
		}
		else if (model_type == 'd') {
			//Start with no force on the particle
			force_x = 0;
			force_y = 0;
			//are the selection of cells empty? 
			for(int i = 0; i < 8; ++i) {
				int val = getNValue(i,'d');
				//Force update criteria:
				if (val == LatType::Empty) {
					val = 0;
				}
				else if (val == LatType::Full) {
					val = 1;
				}
				else if (val == NULL) { //assume boundary of occupied cells
					val = 1;
				}
				switch (i) {
					case 0:
						force_x -= val;
						break;
					case 1:
						force_x -= val;
						force_y -= val;
						break;
					case 2:
						force_y -= val;
						break;
					case 3:
						force_x += val;
						force_y -= val;
						break;
					case 4:
						force_x += val;
						break;
					case 5:
						force_x += val;
						force_y += val;
						break;
					case 6:
						force_y += val;
						break;
					case 7:
						force_x -= val;
						force_y += val;
						break;
					default:
						cout << "If you see this, something is broken.\n";
				}
			}
			//"Normalize"
			if (force_x > 1) {
				force_x = 1;
			}
			else if (force_x < -1) {
				force_x = -1;
			}
			else {
				force_x = 0;
			}
			if (force_y > 1) {
				force_y = 1;
			}
			else if (force_y < 1) {
				force_y = -1;
			}
			else {
				force_y = 0;
			}
		}
	}
	else {
		cout << "Model type specified incorrectly when updating forces!\n";
		force_x = 0;
		force_y = 0;
	}
}

//Sets to the force of an element to be a given value
void LatElem::setForce(int x, int y) {
	force_x = x;
	force_y = y;
}

//Sets the force of an elements neighbour to a given value
void LatElem::setNForce(int nIndex, int x, int y) {
	neighbours[nIndex]->setForce(x,y);
}

//Returns the direction of the force
int LatElem::getForceDir(void) {
	int forceDir = convertXYDir(force_x,force_y); 
	return forceDir;
}

//Returns the force direction of a neighbour
int LatElem::getNForceDir(int nIndex) {
	int forceDir = neighbours[nIndex]->getForceDir();
	return forceDir;
}

//Returns the magnitude of the force
double LatElem::getForceMag(void) {
	double forceMag = (force_x*force_x + force_y*force_y);
	forceMag = pow(forceMag,0.5); 
	return forceMag; 
}

//Return the x component of the force
int LatElem::getForceX(void) {
	return force_x;
}

//Return the y component of the force
int LatElem::getForceY(void) {
	return force_y;
}

//Get burn time
void LatElem::setBurnTime(int newval) {
	burn_time = newval;
}

//Set burn time
int LatElem::getBurnTime(void) {
	return burn_time;
}

//Return true if the lattice element has LatType::Empty
bool LatElem::isEmpty(void) {
	bool toreturn = false;
	if (getValue() == Empty) {
		toreturn = true;
	}
	return toreturn;
}

//Return true if the neighbour element has LatType::Empty
bool LatElem::isNEmpty(int k) {
	bool toreturn = false;
	if (getNValue(k) == Empty) {
		toreturn == true;
	}
	else if (getNValue(k) == NULL) {
		toreturn == true;
	}
	return toreturn;
}

//Return the value of a lattice element as an integer
LatElem::LatType LatElem::getValue(void) { 
	return value; 
}

//Return the value of the one of the neighbours
LatElem::LatType LatElem::getNValue(int nIndex, char model) {
	if (neighbours[nIndex] == NULL) {
		if (model == 'd') {
			return LatElem::Full; 
		}
		else if (model = 'g') {
			return LatElem::Empty; 
		}
		else {
			return LatElem::Empty; 
		}
	}
	return neighbours[nIndex]->getValue(); 
}

//Return the force_x value of one of the neighbours
int LatElem::getNForceX(int nIndex) {
	if (neighbours[nIndex] == NULL) return 0; 
	return neighbours[nIndex]->getForceX();
}

//Return the force_y value of one of the neighbours
int LatElem::getNForceY(int nIndex) {
	if (neighbours[nIndex] == NULL) return 0; 
	return neighbours[nIndex]->getForceY();
}

//Make a specific cell empty
void LatElem::makeEmpty(void) {
	value = LatType::Empty;
	force_x = 0;
	force_y = 0;
	burn_time = 0;
}

//Make a specific neighbour empty
void LatElem::makeNEmpty(int nIndex) {
	if (!(neighbours[nIndex] == NULL)) neighbours[nIndex]->makeEmpty();
}

//Return a Neighbour
LatElem* LatElem::getNeighbour(int i) {
	return neighbours[i];
}

//Set the value of a specific neighbouring cell
void LatElem::setNeighbours(int nIndex, LatElem& neighbour) {
	neighbours[nIndex] = &neighbour; 
}

//Set the neighbours of the lattice element to be null-pointers
void LatElem::setNullNeighbours(void) { 
	for (int i = 0; i < 8; i++) { 
		neighbours[i] = NULL; 
	}
}

//Convert components into a xy direction
int convertXYDir(int x, int y) {
	int jensenval;
	if(x > 0) { 
		if (y > 0) jensenval = 1; 
		else if (y < 0) jensenval = 7; 
		else if (y == 0) jensenval = 0; 
	}
	else if (x < 0) { 
		if (y == 0) jensenval = 4; 
		else if (y > 0) jensenval = 3; 
		else if (y < 0) jensenval = 5; 
	} 
	else if (x == 0) { 
		if (y == 0) jensenval = 8; 
		else if (y > 0) jensenval = 2; 
		else if (y < 0) jensenval = 6;
	}
	else { //should never happen, default case
		cout << "ERROR: Problem converting x and y value into Jensen Notation!\n"
			 << "Using default value of 8 (0,0)\n";
		jensenval = 8; 
	}
	return jensenval;
}