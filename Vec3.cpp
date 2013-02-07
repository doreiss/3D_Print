#include "Vec3.h"

Vec3::Vec3(void) {
	x = 0; 
	y = 0; 
	z = 0; 
	int pos = 0; 
}

Vec3::Vec3(double xInit, double yInit, double zInit) { 
	x = xInit; 
	y = yInit; 
	z = zInit; 
	int pos = 0; 
}

double Vec3::getX(void) {
	return x; 
}
double Vec3::getY(void) { 
	return y; 
} 
double Vec3::getZ(void) { 
	return z; 
} 

void Vec3::setX(double xInit) { 
	x = xInit; 
}

void Vec3::setY(double yInit) { 
	y = yInit;
}

void Vec3::setZ(double zInit) { 
	z = zInit; 
}

bool Vec3::withinResolution(Vec3 other, double resolution) { 
	bool condX = (abs(x - other.getX()) > resolution);
	bool condY = (abs(y - other.getY()) > resolution);
	bool condZ = (abs(z - other.getZ()) > resolution);
	return (condX || condY || condZ); 
}