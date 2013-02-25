// Main file for running the grid window application.
#include <QApplication>
#include "gridwindow.h"
#include "Model.h"
#include "FireModel.h"
#include "GasModel.h"
#include "OptionPane.h"
#include "Lattice.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {	
	QApplication app(argc, argv);
	
	OptionPane options(NULL); 
	options.show();

	return app.exec();
}