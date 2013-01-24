#include <iostream>
#include "Lattice.h"
#include "LatElem.h"
using namespace std; 

int main() {
	Lattice test(10,10,0);
	Lattice test2(2,2,1); 
	test.insertSubLattice(test2,2,2); 
	test.insertSubLattice(test2,6,6); 
	test.print(); 
	return 0; 
}
