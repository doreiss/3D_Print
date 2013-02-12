#include "Vec3.h"

//Default constructor 0,0,0
Vec3::Vec3(void) {
	x = 0; 
	y = 0; 
	z = 0; 
}

//Constructor for 3 given doubles: x, y, & z
Vec3::Vec3(double xInit, double yInit, double zInit) { 
	x = xInit; 
	y = yInit; 
	z = zInit; 
}

//Return x
double Vec3::getX(void) {
	return x; 
}

//Return y
double Vec3::getY(void) { 
	return y; 
} 

//Return z
double Vec3::getZ(void) { 
	return z; 
} 

//Set x
void Vec3::setX(double xInit) { 
	x = xInit; 
}

//Set y
void Vec3::setY(double yInit) { 
	y = yInit;
}

//Set z
void Vec3::setZ(double zInit) { 
	z = zInit; 
}

//Return true if the difference with this and another given vector is greater than a given resolution
//Applies to all data members separately
bool Vec3::withinResolution(Vec3 other, double resolution) { 
	bool condX = (abs(x - other.getX()) > resolution);
	bool condY = (abs(y - other.getY()) > resolution);
	bool condZ = (abs(z - other.getZ()) > resolution);
	return (condX || condY || condZ); 
}
