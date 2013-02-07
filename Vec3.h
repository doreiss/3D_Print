#pragma once 
#include <vector> 
#include <iostream> 

class Vec3
{
public:
	Vec3(void); 
	Vec3(double,double,double); 
	double getX(void); 
	double getY(void); 
	double getZ(void);
	void setX(double); 
	void setY(double); 
	void setZ(double); 
	bool withinResolution(Vec3,double); 
private:
	double x;
	double y; 
	double z;
}; 