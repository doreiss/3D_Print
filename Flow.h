#pragma once
#include "Lattice.h"
#include "LatElem.h"
#include <fstream>
#include <string>

//Flow = vector<Lattice>

class Flow
{
public:
	//Constructors
	//Default empty
	Flow(void);
	//Specify initial row, column
	Flow(int,int);
	//From a single initial lattice
	Flow(Lattice&,bool = true);
	//From a file
	Flow(string);

	//Methods
	//Return the column size of the flow file
	int getCols(void);
	//Return the row size of the flow file
	int getRows(void);
	//Return the number of total lattice states in the vector
	int numStates(void);
	//Add a lattice to end of the file
	void addLattice(Lattice);
	//Add a lattice after a given line number (0 for beginning)
	void addLattice(Lattice,int);
	//Return a lattice object at a given time
	Lattice readLattice(int);
	//Returtn the last lattice object in the flow
	Lattice readLattice(void);
	//Cout a specific lattice state
	void print(int);
	//Cout last lattice state
	void print(void);
	//Print information to .flow file
	//void filePrint(void);

private:
	//number of columns per lattice
	int rows;
	//number of rows per lattice
	int cols;
	//Vector of lattices
	vector<Lattice> system;
} ;

//Functions