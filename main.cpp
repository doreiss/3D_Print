#include <iostream>
#include "Lattice.h"
#include "LatElem.h"
using namespace std; 

int main() {
	//Some test cases for the lattice, does it work ok?
	Lattice test(10,10,0);
	Lattice test2(2,2,1); 
	test.insertSubLattice(test2,2,2); 
	test.insertSubLattice(test2,6,6);
	cout << test.getElement(9,9).getNValue(0) << endl; 
	test.print(); 
	return 0; 
}
