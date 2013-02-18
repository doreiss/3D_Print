#include <iostream>
#include <sstream>
#include "Lattice.h"
#include "LatElem.h"
#include "Flow.h"
#include "Model.h"
#include "GasModel.h"
#include "FireModel.h"
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

	Lattice test = f1.getLattice();
	test.print();

	test = f1.getLattice(0);
	test.print();

	test = f1.getLattice(-1);
	test.print();

	test = f1.getLattice(2);
	test.print();
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
	Lattice l(rows,cols,LatElem::Empty);
	l.setSubLattice(7,17,7,17,t); 
	FireModel g(l);
	g.iterate(5);
	
	CubeArray cube(g,3,false);
	Polyhedron P(cube,0.0005,1);
	P.print_ply("plytest.ply");
	//P.print_stl("stltest.stl");

	return 0; 
}
