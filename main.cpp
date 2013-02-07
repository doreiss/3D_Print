#include <iostream>
#include "Lattice.h"
#include "LatElem.h"
#include "Gas.h"
#include "Flow.h"

using namespace std; 
int main() {
	Lattice testificate(10,10,1);

	Flow f2(10,10);
	Flow f3(testificate,false);
	Flow f4(testificate,true);

	cout << f2.getCols() << '\t';
	cout << f3.getCols() << '\t';
	cout << f4.getRows() << '\n';
	

	//Some test cases for the lattice, does it work ok?
	/*
	Lattice L("lattice.flow",false,1);

	L.print();
	*/

	/*
	Lattice test(10,10,1); 
	test.setSubLattice(1,8,1,8,0); 
	test.setSubLattice(3,6,3,6,1);
	Gas model(test);
 	for(int i = 0; i < 21; i++) {
		model.iterate();
		model.filePrint(false); //not a human file
	}
	model.print();
	model.filePrintAll();

	
	Lattice test2(20,20,1);
	test2.filePrint(false,true);
	test2.fileRead(1);
	//cout << "\n\nNumber of lines: " << fileLines() << "\n";
	*/
	return 0; 
}
