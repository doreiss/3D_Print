#include "Gas.h"
#include "Lattice.h"
#include "LatElem.h"
#include <cmath> 

using namespace std;

Gas::Gas(void) { //default empty constructor
}

Gas::Gas(Lattice initial) { //default constructor for a given lattice object
	state = initial;
}

void Gas::iterate(void) {
	//Add rules based on Appendix B from Jensen's book
}

