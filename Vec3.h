#pragma once 
#include <vector> 
#include <iostream> 

//3D Vector Class of doubles x, y, z
class Vec3
{
public:
	//Constructors
	//Default constructor
	Vec3(void);
	//Construct a vec3 of 3 given doubles: x, y, z.
	Vec3(double,double,double); 
	//Return x
	double getX(void); 
	//Return y
	double getY(void);
	//Return z
	double getZ(void);
	//Set x
	void setX(double);
	//Set y
	void setY(double);
	//Set z
	void setZ(double); 
	//Resolution check (Return true if difference between 2 vectors is greater than given double (for all elements))
	bool withinResolution(Vec3,double); 
private:
	//Cartesian coordinates
	double x;
	double y; 
	double z;
}; 