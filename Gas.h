#pragma once
#include "LatElem.h"
#include "Lattice.h"
#include <vector>
#include <cmath> 

// Lattice gas model

class Gas 
{
public:
	//Constructors
	//Default constructor
	Gas(void);
	//Create a gas using a given lattice
	Gas(Lattice&);
	//Create a gas using from a given state in a .flow file

	//Methods
	//Return a pointer to a lattice of the current gas state
	Lattice* getLattice(void);
	//Update gas to next time step
	void iterate(void);
	//Update gas n times
	void iterate(int); 
	//Print current gas state to cout
	void print(void);
	//Print current gas state to file
	void filePrint(bool);
	//Print all gas states to file/entire flow object - merge to filePrint (overload)
	void filePrintAll(void);
	//Returns the number of time steps taken
	int timeSize(void); 
	//return the current gas state at a time t as a lattice
	Lattice getLatT(int); 

private:
	//Lattice representing current gas states
	Lattice* state;
	//Vector containing all gas states, initial to current
	vector < Lattice >  flow;
};