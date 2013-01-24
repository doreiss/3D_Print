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
	Gas(Lattice); //Constructor
	void iterate(void);

private:
	Lattice state;
};