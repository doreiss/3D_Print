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
	/*
	//Some test cases for flow objects
	Lattice l1(10,10,LatElem::Full);
	Lattice l2(10,10,LatElem::Empty);

	Flow f1(l1,true);
	f1.addLattice(l2);

	Lattice l2b = f1.readLattice();
	l2b.print();

	Lattice l1b = f1.readLattice(0);
	l1b.print();

	Lattice l3b = f1.readLattice(-1);
	l3b.print();
	*/

	//Some test cases for the lattice, does it work ok?
	//This section below does not work - fix this, check constructor of lattice given a flow object/file
	/*
	Lattice L("lattice.flow",false,1);

	L.print();
	*/

	//This all works
	/*
	Lattice test(10,10,LatElem::Full); 
	test.setSubLattice(1,8,1,8,LatElem::Empty); 
	test.setSubLattice(3,6,3,6,LatElem::Full);
	Gas model(test);
 	for(int i = 0; i < 21; i++) {
		model.iterate();
		model.filePrint(false); //not a human file
	}
	model.print();
	model.filePrintAll();

	Lattice test2(20,20,LatElem::Full);
	test2.filePrint(false,true);
	test2.fileRead(1);
	//cout << "\n\nNumber of lines: " << fileLines() << "\n";
	*/

	
	int rows = 25; 
	int cols = 25; 
	LatElem::LatType t = LatElem::Full;
	srand(time(NULL)); 
	Lattice l(rows,cols,t); 
	l.setSubLattice(1,rows - 2,1,cols - 2,LatElem::Empty); 
	l.setSubLattice(7,17,7,17,t); 
	Gas g(l,Gas::forest_fire);
	g.iterate(10); //there is a problem here
	CubeArray cube(g,3,true);
	Polyhedron P(cube,0.0005,1);
	P.print_ply("plytest.ply");
	//P.print_stl("stltest.stl");

	return 0; 
}
