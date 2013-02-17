#include <iostream>
#include <sstream>
#include "Lattice.h"
#include "LatElem.h"
#include "Gas.h"
#include "Flow.h"
#include "CubeArray.h" 
#include "CubeElem.h"
#include "Polyhedron.h"
#include <ctime>

using namespace std; 
int main() {
	Lattice l1(10,10,LatElem::Full);
	Lattice l2(10,10,LatElem::Empty);

	Flow f1(l1,false);
	f1.addLattice(l1,0);
	f1.addLattice(l2,1);

	f1.print();

	Flow f2(l1,false);
	f2.addLattice(l1,0);
	f2.addLattice(l2,0);

	f2.print();

	//Some test cases for the lattice, does it work ok?
	//This section below does not work - fix this, check constructor of lattice given a flow object/file
	/*
	Lattice L("lattice.flow",false,1);

	L.print();
	*/

	//This all works
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

	/*
	int rows = 25; 
	int cols = 25; 
	LatElem::LatType t = LatElem::Full;
	srand(time(NULL)); 
	Lattice l(rows,cols,t); 
	l.setSubLattice(1,rows - 2,1,cols - 2,LatElem::Empty); 
	l.setSubLattice(7,17,7,17,t); 
	Gas g(l);
	g.iterate(10);
	CubeArray cube(g,3,true);
	Polyhedron P(cube,0.0005,1);
	P.print_ply("plytest.ply");
	//P.print_stl("stltest.stl");
	*/

	return 0; 
}
