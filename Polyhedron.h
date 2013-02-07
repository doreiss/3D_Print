#pragma once 
#include <vector> 
#include <iostream> 
#include <string>
#include <fstream>
#include "Vec3.h"
#include "Face.h"
#include "CubeArray.h"
#include "CubeElem.h"
using namespace std; 
class Polyhedron
{
public:
	Polyhedron(void);
	Polyhedron(CubeArray,double,double);
	int vertSize(void);
	int faceSize(void);
	Vec3* getVertex(int);
	Face* getFace(int); 
	void constructVF(int,int,int,int,double);
	int addVertex(Vec3&);
	void print_stl(string = "test.stl", string = "OBJNAME"); 
	void stl_head(ofstream&,string); 
	void stl_foot(ofstream&,string); 
	void stl_facet(ofstream&); 
	void print_ply(string = "test.ply"); 
	void ply_head(ofstream&);
	void ply_vertex(ofstream&);
	void ply_faces(ofstream&);
private:
	vector < Vec3 > vert;
	vector < Face > faces;
	double resolution;
};