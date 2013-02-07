#include "Face.h"

Face::Face(void) { 
}

Face::Face(vector <int > vertInit, Vec3 nInit) { 
	setVerticies(vertInit); 
	setNormal(nInit); 
}

Vec3 Face::getNormal(void) { 
	return normalVector; 
}

void Face::setNormal(Vec3  nInit) {
	normalVector = nInit; 
}

int Face::getOrder(void) { 
	return verticies.size(); 
}

vector <int> Face::getVerticies(void) { 
	return verticies; 
}

void Face::setVerticies(vector <int> vertInit) { 
	verticies = vertInit; 
}