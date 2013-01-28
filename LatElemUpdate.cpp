#include "Latelemupdate.h"
#include <iostream>

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
void LatElemUpdate::setForce(int x_init, int y_init) {
	forcevalue[0] = x_init;
	forcevalue[1] = y_init;
}

//Other methods to follow