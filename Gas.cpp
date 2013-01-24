#include "Gas.h"
#include "Lattice.h"
#include "LatElem.h"
#include <cmath> 

using namespace std;

Gas::Gas(void) {
}

Gas::Gas(Lattice initial) {
	state = initial;
}

void Gas::iterate(void) {
	//Add rules based on Appendix B from Jensen's book
}

