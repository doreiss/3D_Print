#include <iostream>
#include <sstream>
#include "Lattice.h"
#include "LatElem.h"
#include "Gas.h"
#include "CubeArray.h" 
#include "CubeElem.h"
#include "Polyhedron.h"
#include <ctime>

using namespace std; 

int main() {
	int rows = 25; 
	int cols = 25; 
	int p = 20;
	LatElem::LatType t = LatElem::Full;
	srand(time(NULL)); 
	Lattice l(rows,cols,t); 
	l.setSubLattice(1,rows - 2,1,cols - 2,LatElem::Empty); 
	l.setSubLattice(4,10,4,10,t); 
	Gas g(l);
	g.iterate(5);
	CubeArray cube(g,3,true);
	Polyhedron P(cube,0.0005,1);
	P.print_ply("plytest.ply");
	//P.print_stl("stltest.stl");
	return 0; 
}
