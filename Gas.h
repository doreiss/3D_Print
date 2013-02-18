#pragma once
#include "LatElem.h"
#include "Lattice.h"
#include "Flow.h"
#include <vector>
#include <cmath> 

// Lattice gas model & "Makeshift" Forest Fire
// Forest Fire Percentage
#define GROWTH 20
#define LIGHTNING_BASE 1
#define LIGHTNING_GROWTH 2
#define BURNING_SPREAD 50
#define BURNING_TIME 2

class Gas
{
public:

enum Model {
	static_gas,
	dynamic_gas,
	forest_fire,
};


	//Constructors
	//Default constructor
	Gas(void);
	//Create a gas using a given lattice
	Gas(Lattice&,Model = static_gas);
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
	//Model type
	Model system_type;
	//Lattice representing current gas states
	Lattice* state;
	//Vector containing all gas states, initial to current
	Flow system_states;

};

//Functions
int random(void);