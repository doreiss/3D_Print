// Main file for running the grid window application.
#include <QApplication>
#include "gridwindow.h"
#include "Gas.h"
#include "Lattice.h"
//#include "timerwindow.h"
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
	int p = 45;
	srand(time(NULL)); 
	Lattice l(rows,cols,1); 
	l.setSubLattice(1,rows - 2,1,cols - 2,0); 
	for(int i = 1; i < rows - 1; i++) { 
		for(int j = 1; j< rows -1; j++) {
			
			int ptest = rand() % 100;  
			if (ptest < p) l.setElement(i,j,1); 
		} 
	}
	Gas g(l); 
    GridWindow widget(g,NULL);
    widget.show();
    return app.exec();
}