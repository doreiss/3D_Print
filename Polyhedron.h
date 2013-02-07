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
	//Constructors
	//Default
	Polyhedron(void);
	//Constructs a Polyhedron based on an existing cube array, a defined minimum resolution of verticies, and a characteristic cube size
	Polyhedron(CubeArray,double,double);
	//Returns how many verticies define this polyhedron
	int vertSize(void);
	//Returns how many faces this polyhedron has
	int faceSize(void);
	//Returns a pointer to the vertex of a given index
	Vec3* getVertex(int);
	//Returns a pointer to the face of a given index
	Face* getFace(int); 
	//Constructs the verticies and faces of 2 triangle faces whcih together form a square in the polyhedron
	//Takes the row, col, stack index, face index and cubeSize, triangulates that cube face and adds it to the polyhedron
	void constructVF(int,int,int,int,double);
	//Adds a vertex to the Polyhedron if it doesnt already exist and returns the index of newvertex or equivalent existing vetex
	int addVertex(Vec3&);
	//Prints the polyhedron to a .stl file with filename and object name
	void print_stl(string = "test.stl", string = "OBJNAME");
	//Prints hte polyhedron to a .ply file with filename and object name
	void print_ply(string = "test.ply"); 
private:
	vector < Vec3 > vert;
	vector < Face > faces;
	double resolution;
	
	//Prints the header of a .stl file with objname to outfile
	void stl_head(ofstream&,string); 
	//Prints the footer of a .stl file with objname to outfile
	void stl_foot(ofstream&,string); 
	//Prints the complete facet information of a .stl file to outfile
	void stl_facet(ofstream&); 
	//Prints the header of a .ply file to outfile
	void ply_head(ofstream&);
	//Prints the complete vertex infomation of a .ply file to outfile
	void ply_vertex(ofstream&);
	//Prints the complete face information of a .ply file to outfiles
	void ply_faces(ofstream&);
};