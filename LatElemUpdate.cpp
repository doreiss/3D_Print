
#include "LatElemUpdate.h"
#include <iostream>
#include <cmath>
using namespace std;

//Default (Empty) Constructor
LatElemUpdate::LatElemUpdate(void) {
	forcevalue[0] = 0;
	forcevalue[1] = 0;
}

//Constructor for given values
LatElemUpdate::LatElemUpdate(int x_init,int y_init) {
	forcevalue[0] = x_init;
	forcevalue[1] = y_init;
}

//Method for setting the force
void LatElemUpdate::setForces(int x_init, int y_init) {
	forcevalue[0] = x_init;
	forcevalue[1] = y_init;
}

int LatElemUpdate::getForceDir(void) {
	int dir = convertXYDir(forcevalue[0],forcevalue[1]);
	return dir; //test
}

int LatElemUpdate::getForceMag(void) { 
	int mag = (forcevalue[0]*forcevalue[0])+(forcevalue[1]*forcevalue[1]);
	mag = pow(mag,0.5); 
	return mag;
}

int convertXYDir(int x,int y) { 
	if( x>0 ) { 
		if (y == 0) return 0; 
		if (y > 0) return 1; 
		if (y < 0) return 7; 
	}
	else if (x < 0) { 
		if (y == 0) return 4; 
		if (y > 0) return 3; 
		if (y < 0) return 5; 
	} 
	else if (x == 0) { 
		if (y == 0) return 8; 
		if (y > 0) return 2; 
		if (y < 0) return 6; 
	}
	else return 8; 
}
