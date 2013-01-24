#include <iostream>
#include "Lattice.h"
#include "LatElem.h"
using namespace std; 

int main() {
	Lattice test(5,5,1);
	test.setSubLattice(1,3,1,3,0);
	for (int i = 0; i < 8; i++) {
		 cout << test.getElement(1,1).getNValue(i) << "\t"; 
	}
	cout << endl; 

	test.print(); 
	return 0; 
}
