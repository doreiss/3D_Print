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
#include <cstdlib>

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

	int rows = 20;
	int cols = 20;
	LatElem::LatType t = LatElem::Full;
	LatElem::LatType e = LatElem::Empty;
	srand(time(NULL));
	Lattice l(rows+2,cols+2,t);
	l.setSubLattice(1,rows,1,cols,e);
	l.setSubLattice(10,11,10,11,t);
	l.filePrint(true,true);
	GasModel* g = new GasModel(l);
	cout << "Lattice generated successfully\n";
	/*
	l.setElement(0,0,t);
	l.setElement((rows-1),(cols-1),t);
	l.setElement(0,(cols-1),t);
	l.setElement((rows-1),0,t);
	DynGasModel* g = new DynGasModel(l);
	*/
	g->iterate(40);
	cout << "Model iterated successfully\n";
	CubeArray cube(g,3,false);
	Polyhedron P(cube,0.0005,0.25);
	P.print_ply("gastest2020.ply");
	cout << ".ply file printed successfully\n";


	/*
	//Just want types 0 - 3;
	LatElem::LatType A = LatElem::Empty;
	LatElem::LatType B = LatElem::Full;
	LatElem::LatType C = LatElem::Burning;
	LatElem::LatType D = LatElem::Boundary;
	Lattice l1(5,5,A);
	for (int i = 1; i <= 3; ++i) {
		l1.setElement(i,2,C);
		if (i == 1) {
			l1.setElement(i,1,B);
			l1.setElement(i,3,D);
		}
		else {
			l1.setElement(i,1,D);
			l1.setElement(i,3,B);
		}
	}
	l1.print();

	LatElem* test = l1.getElement(2,2);
	cout << "(2,2)" << '\t' << test->getValue() << '\n';
	for (int k = 0; k <= 7; ++k) {
		cout << k << '\t' << test->getNValue(k) << '\n';
	}
	*/

	return 0; 
}
