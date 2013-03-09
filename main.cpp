#include <iostream>
#include <sstream>
#include <string>
#include "Lattice.h"
#include "LatElem.h"
#include "Flow.h"
#include "Model.h"
#include "GasModel.h"
#include "FireModel.h"
#include "DynGasModel.h"
#include "CubeArray.h" 
#include "CubeElem.h"
#include "Polyhedron.h"
#include <ctime>

using namespace std; 
int main() {

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

	int rows = 50;
	int cols = 50;
	LatElem::LatType t = LatElem::Full;
	srand(time(NULL));
	Lattice l(rows,cols,LatElem::Empty);
	l.setSubLattice(25,26,25,26,t);
	DynGasModel* g = new DynGasModel(l);
	g->iterate(10);
	CubeArray cube(g,3,false);
	Polyhedron P(cube,0.0005,0.25);
	P.print_ply("dyngas2020test.ply");

	return 0; 
}
