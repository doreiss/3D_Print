#pragma once //compile only once (replace #ifendf etc)
#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include "LatElem.h"
using namespace std; 
class Lattice
{
public:
	//Constructors
	Lattice(void);
	Lattice(int, int, int);
	Lattice(char*, bool); //bool for different filetypes - human/computer readable files
	Lattice(string, int);
	//Lattice(ifstream&, int);
	
	//Functions
	void setElement(int, int, int); //set a specific element - row, column, value
	void insertSubLattice(Lattice, int, int); //insert another lattice object as a sublattice
	/*
		sub-lattice to be inserted, top left row position, top right row position
		corresponds to point of insertion
	*/
	void updateForces(void); //updatr all the force elements
	int getElemVal(int,int); //get the value of a specific element
	LatElem* getElement(int,int); //get a 'Lat_elem' object (includes pointers to neighbours)
	int rowSize(void); //get the row size
	int colSize(void); //get the column size
	bool isEmpty(int, int); //is the lattice empty?
	void setSubLattice(int,int,int,int,int); //create a sub lattice
	/*
		first row index, last row index
		first column index, last column index

	*/
	//asdf
	void print(void); //cout lattice values
	void filePrint(bool,bool,int); //print lattice values to file
	void filePrint(bool,bool);
	void fileRead(int); //read a lattice from a file lattice.flow
	void fileRead(string,int); //ditto, from a general filename.flow

private: 
	void setElementNeighbours(void);
	vector< vector < LatElem > > values; //vector of vectors of lattice elements
};

int findMax(vector<int>); 

int convertDirX(int); 
int convertDirY(int);

int fileLines(void);
int fileLines(string);
int fileLines(ifstream&);
