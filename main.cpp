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
	int rows = 15; 
	int cols = 15; 
	int p = 20;
	srand(time(NULL)); 
	Lattice l(rows,cols,1); 
	l.setSubLattice(1,rows - 2,1,cols - 2,0); 
	l.setSubLattice(2,4,2,4,1);
	l.setSubLattice(2,4,10,12,1);
	l.setSubLattice(10,12,2,4,1);
	l.setSubLattice(10,12,10,12,1);
	Gas g(l); 
	g.iterate(5); 
	CubeArray cube(g);
	cube.print_stl("test.stl");
}
