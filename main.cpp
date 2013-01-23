#include <iostream>
#include "Lattice.h"

using namespace std; 

int main() {
	Lattice test(5,5,1);
	test.setSubLattice(1,3,1,3,0); 
	test.print(); 
	return 0; 
}
