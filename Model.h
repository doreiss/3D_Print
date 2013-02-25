#pragma once

#include <iostream> 
#include <vector>
#include "Lattice.h"
#include "Flow.h"

class Model 
{
public: 
	//Constructors 
	Model(); 
	Model(Lattice&);

	//Methods
	//Return a pointer to a lattice of the current model state
	Lattice* getLattice(void);
	//Print current model state to cout
	void print(void);
	//Print current model state to file
	void filePrint(bool);
	//Print all model states to file/entire flow object - merge to filePrint (overload)
	void filePrintAll(void);
	//Returns the number of time steps taken
	int timeSize(void); 
	//return the current gas state at a time t as a lattice
	Lattice getLatT(int);
	//Virtual iterate function
	virtual void iterate(void) = 0; 
protected:
	//Current state
	Lattice* state;
	//Vector containing all model states, initial to current
	Flow system_states;
};