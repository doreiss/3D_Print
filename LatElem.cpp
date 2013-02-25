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
void LatElem::setForce(char& model_type) {
	if (model_type == 'g' || model_type == 'd' || model_type == 's') {
		if (value == 0) {
			force_x = 0;
			force_y = 0;
		}
		if (model_type == 'g') {
			force_x = getNValue(4) - getNValue(0); 
			force_y = getNValue(6) - getNValue(2);
		}
		else if (model_type == 's') { //Strongest side wins - leaving in incase useful
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
		else if (model_type == 'd') {
			//are the selection of cells empty? 
			int right = 0; //7,0,1
			int left = 0; //3,4,5
			int top = 0; //1,2,3
			int bottom = 0; //5,6,7
			for(int i = 0; i <= 7; ++i) {
				int val = getNValue(i);
				switch (i) {
					case 0:
						right += val;
						break;
					case 1:
						right += val;
						top += val;
						break;
					case 2:
						top += val;
						break;
					case 3:
						top += val;
						left += val;
						break;
					case 4:
						left += val;
						break;
					case 5:
						left += val;
						bottom += val;
						break;
					case 6:
						bottom += val;
						break;
					case 7:
						bottom += val;
						right += val;
						break;
					default:
						cout << "If you see this, you've really broken something.\n";
						break;
				}
			}
			//x dir
			if (right == 0 && left > 0) {
				force_x = 1;
			}
			else if (right > 0 && left == 0) {
				force_x = -1;
			}
			else {
				force_x = 0;
			}
			//y dir
			if (top == 0 && bottom > 0) {
				force_y = 1;
			}
			else if (top > 0 && bottom == 0) {
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

//Returns the direction of the force
int LatElem::getForceDir(void) {
	int forceDir = convertXYDir(force_x,force_y); 
	return forceDir;
}

//Returns the magnitude of the force
double LatElem::getForceMag(void) {
	double forceMag = (force_x*force_x + force_y*force_y);
	forceMag = pow(forceMag,0.5); 
	return forceMag; 
}

//Get burn time
void LatElem::setBurnTime(int newval) {
	burn_time = newval;
}

//Set burn time
int LatElem::getBurnTime(void) {
	return burn_time;
}

//Return true if the lattice element has Latype::Empty
bool LatElem::isEmpty(void) {
	bool toreturn = false;
	if (getValue() == Empty) {
		toreturn = true;
	}
	return toreturn;
}

//Return the value of a lattice element as an integer
LatElem::LatType LatElem::getValue(void) { 
	return value; 
}

//Return the value of the one of the neighbours
LatElem::LatType LatElem::getNValue(int nIndex) {
	if (neighbours[nIndex] == NULL) return LatElem::Empty; 
	return neighbours[nIndex]->getValue(); 
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