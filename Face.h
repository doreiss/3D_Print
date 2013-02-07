#pragma once 
#include <vector> 
#include <iostream> 
#include "Vec3.h"
using namespace std; 
class Face
{
public:
	Face(); 
	Face(vector <int>,Vec3);
	Vec3 getNormal(void); 
	void setNormal(Vec3); 
	int getOrder(void); 
	vector <int> getVerticies(void); 
	void setVerticies(vector <int>); 
private:
	vector < int >  verticies;
	Vec3 normalVector;
};