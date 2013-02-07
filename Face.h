#pragma once 
#include <vector> 
#include <iostream> 
#include "Vec3.h"
using namespace std; 
class Face
{
public:
	//Constructors: 

	//Default
	Face(); 
	//Creates a face with vertex indicies (vector < int >) and a normal vector (Vec3)
	Face(vector < int >,Vec3);
	
	//Methods:
	
	//Returns the normal vector to this face
	Vec3 getNormal(void); 
	//Set the normal vector of this face
	void setNormal(Vec3); 
	//Returns the number of verticies whcih defines this face
	int getOrder(void); 
	//Get the vertex indicies of this face in a vector 
	vector < int > getVerticies(void); 
	//Set the vertex indicies of this face
	void setVerticies(vector <int>);

private:
	//The vertex indicies which define the face
	vector < int >  verticies;
	//The unit vector normal to this face
	Vec3 normalVector;

};