#include <iostream>
#include <sstream>
#include "Lattice.h"
#include "LatElem.h"
#include "Gas.h"
#include "CubeArray.h" 
#include "CubeElem.h"

using namespace std; 

int main() {
	Lattice test2(10,20,1);
	test2.filePrint(false,true);
	test2.fileRead(1);

	return 0; 
}
