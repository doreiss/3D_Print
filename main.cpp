#include <iostream>
#include "Lattice.h"
#include "LatElem.h"
#include "Gas.h"

using namespace std; 

int main() {
	//Some test cases for the lattice, does it work ok?
	Lattice test(10,10,1); 
	test.setSubLattice(1,8,1,8,0); 
	test.setSubLattice(3,6,3,6,1);
	Gas model(test);
 	for(int i = 0; i < 21; i++) {
		model.iterate();
		model.fileprint(false); //not a human file
	}
	model.print();
	model.fileprint(true);
	//cout << model.timeSize() << endl; 

	return 0; 
}
