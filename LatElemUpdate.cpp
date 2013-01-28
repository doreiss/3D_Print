
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
