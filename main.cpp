#include <iostream>
#include <sstream>
#include "Lattice.h"
#include "LatElem.h"
#include "Gas.h"
#include "CubeArray.h" 
#include "CubeElem.h"

using namespace std; 

int main() {
	CubeArray cube(1,1,1,CubeElem::Full);
	cube.print_stl("test.stl"); 

}
