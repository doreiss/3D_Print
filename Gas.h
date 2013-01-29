#pragma once
#include "LatElem.h"
#include "Lattice.h"
#include <vector>
#include <cmath> 

/* Lattice gas model
*/

class Gas 
{
public:
	Gas(void); //Default constructor
	Gas(Lattice&); //Constructor
	void iterate(void); //Function to update gas lattice
	void print(void); //Prints the lattice
private:
	Lattice* state;
	vector < vector < state >  > flow;
};