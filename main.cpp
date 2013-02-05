#include <iostream>
#include <sstream>
#include "Lattice.h"
#include "LatElem.h"
#include "Gas.h"
#include "CubeArray.h" 
#include "CubeElem.h"
#include <ctime>

using namespace std; 

int main() {
	int rows = 10; 
	int cols = 10; 
	int p = 20;
	LatElem::LatType t = LatElem::Full;
	srand(time(NULL)); 
	Lattice l(rows,cols,t); 
	l.setSubLattice(1,rows - 2,1,cols - 2,LatElem::Empty); 
	l.print(); 
	l.setSubLattice(3,6,3,6,t); 
	Gas g(l); 
	g.iterate(5); 
	CubeArray cube(g);
	cube.print_stl("test.stl");
	return 0; 
}
