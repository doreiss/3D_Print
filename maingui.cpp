// Main file for running the grid window application.
#include <QApplication>
#include "gridwindow.h"
#include "Gas.h"
#include "Lattice.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	int rows = 15; 
	int cols = 15; 
	srand(time(NULL)); 
	Lattice l(rows,cols,LatElem::Full); 
	l.setSubLattice(1,rows - 2,1,cols - 2,LatElem::Empty); 
	Gas g(l); 
    GridWindow widget(g,NULL);
    widget.show();
    return app.exec();
}