#pragma once
#include "LatElem.h"
#include "Lattice.h"

/* Lattice gas model
*/

class Gas 
{
public:
	Gas(void); //Default constructor
	Gas(Lattice); //Constructor
	
	void iterate(void);
private:
	Lattice state;
};