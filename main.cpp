#include <iostream>
#include "Lattice.h"
#include "LatElem.h"
#include "LatElemUpdate.h"
#include "Gas.h"
using namespace std; 

int main() {
	//Some test cases for the lattice, does it work ok?
	Lattice test(10,10,1); 
	test.setSubLattice(1,8,1,8,0); 
	test.setSubLattice(5,6,5,5,1);
	Gas Model(test); 
	Model.print(); 
	Model.iterate(); 
	Model.print(); 
	LatElem elem = test.getElement(5,5);
	elem.setForce(); 
	cout << elem.getValue() << endl; 
	cout << elem.getForce().getForceDir() << endl; 
	
	return 0; 
}
