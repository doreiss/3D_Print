#include <iostream>
#include <ctime>
#include "gridwindow.h"

using namespace std;

GridWindow::GridWindow(Model* g,std::string n, QWidget *parent)
: QWidget(parent) {
	init = true; 
	name = n; 
	model = g; 
	steps = 0;
	speed = 1;
	running = false; 
	int rows = model->getLattice()->rowSize(); 
	int cols = model->getLattice()->colSize(); 
    QHBoxLayout *header = setupHeader();
    QGridLayout *grid = setupGrid(rows,cols);
    QHBoxLayout *buttonRow = setupButtonRow();
	QHBoxLayout *sliderBox = setupSlider();
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addLayout(header);
    layout->addLayout(grid);
    layout->addLayout(buttonRow);
	layout->addLayout(sliderBox); 
    setLayout(layout);
}

GridWindow::~GridWindow() {
    delete title;
}

QHBoxLayout* GridWindow::setupSlider() { 
	QHBoxLayout *sliderBox = new QHBoxLayout();
    sliderBox->setAlignment(Qt::AlignHCenter);

	QSlider* slider = new QSlider(Qt::Horizontal); 
	slider->setTickPosition(QSlider::TicksAbove); 
	slider->setTickInterval(1); 
	slider->setSingleStep(1); 
	slider->setMinimum(1); 
	slider->setMaximum(10); 
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSlider(int))); 
	sliderBox->addWidget(slider); 
	return sliderBox; 
}

QHBoxLayout* GridWindow::setupHeader() {
    QHBoxLayout *header = new QHBoxLayout();
    header->setAlignment(Qt::AlignHCenter);

    this->title = new QLabel("COMPLEX PROCESSES AND 3D PRINTING",this);
    this->title->setAlignment(Qt::AlignHCenter);
    this->title->setFont(QFont("Arial", 25, QFont::Bold));

    header->addWidget(this->title);

    return header;
}

QGridLayout* GridWindow::setupGrid(int rows,int cols) {

    QGridLayout *grid = new QGridLayout();

    grid->setHorizontalSpacing(0);
    grid->setVerticalSpacing(0);
    grid->setSpacing(0);
    grid->setAlignment(Qt::AlignHCenter);

    for(int i=0; i < rows; i++) {
        std::vector<GridCell*> row;
        cells.push_back(row);
        for(int j=0; j < cols; j++) {
			GridCell *cell = new GridCell(model->getLattice()->getElement(i,j),NULL);
			cells.at(i).push_back(cell);
            grid->addWidget(cell,i,j);
            grid->setColumnStretch(j,1);
        }
        grid->setRowStretch(i,1);
    }
    return grid;
}

QHBoxLayout* GridWindow::setupButtonRow() {
    QHBoxLayout *buttonRow = new QHBoxLayout();
    buttonRow->setAlignment(Qt::AlignHCenter);

	QPushButton* stepButton = new QPushButton("STEP");
	stepButton->setFixedSize(100,25);
	connect(stepButton, SIGNAL(clicked()), this, SLOT(handleStep()));
	buttonRow->addWidget(stepButton); 

    QPushButton *startButton = new QPushButton("START/RESUME");
    startButton->setFixedSize(100,25);
    connect(startButton, SIGNAL(clicked()), this, SLOT(handleStart()));
    buttonRow->addWidget(startButton);

    QPushButton *pauseButton = new QPushButton("PAUSE");
    pauseButton->setFixedSize(100,25);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePause()));
    buttonRow->addWidget(pauseButton);  

	QPushButton *exportButton = new QPushButton("EXPORT 3D");
	exportButton->setFixedSize(100,25); 
	connect(exportButton, SIGNAL(clicked()), this, SLOT(handleExport()));
	buttonRow->addWidget(exportButton); 
	
	QPushButton *quitButton = new QPushButton("EXIT");
    quitButton->setFixedSize(100,25); 
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttonRow->addWidget(quitButton);

    return buttonRow;
}

void GridWindow::handleSlider(int s) { 
	exitSetup(); 
	speed = s;
	if (running) {
		handlePause(); 
		handleStart(); 
	}
}

void GridWindow::handleStep() { 
	exitSetup(); 
	timerFired(); 
}

void GridWindow::handleStart() {
	exitSetup(); 
	running = true; 
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerFired()));
    this->timer->start(2000/speed);
}

void GridWindow::handlePause() {
	exitSetup();	
	cout << "Simulation paused at step : " << steps << endl; 
	running = false; 
	this->timer->stop();
	delete this->timer;
}

void GridWindow::handleExport() {
	exitSetup(); 
	std::string filename1 = name; 
	std::string filename2 = name; 
	filename1.append(".stl"); 
	filename2.append(".ply");
	cout << "Constructing cube array ... ";
	CubeArray cArr(model,2,true);
	cout << "done!" << endl; 
	cout << "Constructing polyhedron ... "; 
	Polyhedron poly(cArr, 0.0005, 1.0);
	poly.stretchDim('t',2.0); 
	cout << "done!" << endl; 
	cout << "Exporting geometry ... "; 
	cout << "stl ... "; 
	poly.print_stl(filename1); 
	cout << "ply ..."; 
	poly.print_ply(filename2); 

	//add flow here

	cout << "done!" << endl; 
}

void GridWindow::exitSetup(){
	if(init) {
		cout << "Done setting initial conditions... " << endl; 
		for (int i = 0; i < cells.size(); i++) { 
			for(int j = 0; j < cells[i].size(); j++) { 
				cells[i][j]->off = true;
			}
		}
		init = false; 
	}
}

std::vector<std::vector<GridCell*> >& GridWindow::getCells() {
    return this->cells;
}

void GridWindow::timerFired() {
	steps++;
	cout << "Step : " << steps << endl; 
	model->iterate();
	for(int m=0; m<cells.size(); m++)
	{
		for(int n=0; n<cells.at(m).size(); n++) {
			cells[m][n]->redrawCell();
		}
	}
}

