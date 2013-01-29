#pragma once
#include "LatElem.h"
#include "Lattice.h"
#include <vector>
#include <cmath> 

// Lattice gas model

class Gas 
{
public:
	Gas(void); //Default constructor
	Gas(Lattice&); //Constructor
	Lattice* getLattice(void); 
	void iterate(void); //Function to update gas lattice
	void print(void); //Prints the lattice
	int timeSize(void); //finds the current time step 
	Lattice getLatT(int); //returns the Lattice at time T
private:
	Lattice* state;
	vector < Lattice >  flow; //what is this? - Josh
};