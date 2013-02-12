#include <iostream>
#include <ctime>
#include "gridwindow.h"

using namespace std;

GridWindow::GridWindow(Gas& g, QWidget *parent)
: QWidget(parent)
{
	model = &g; 
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

void GridWindow::ChangeModel(Gas& g, bool border) {
	
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

QHBoxLayout* GridWindow::setupHeader()
{
    QHBoxLayout *header = new QHBoxLayout();
    header->setAlignment(Qt::AlignHCenter);

    this->title = new QLabel("COMPLEX PROCESSES AND 3D PRINTING",this);
    this->title->setAlignment(Qt::AlignHCenter);
    this->title->setFont(QFont("Arial", 25, QFont::Bold));

    header->addWidget(this->title);

    return header;
}

QGridLayout* GridWindow::setupGrid(int rows,int cols, bool border)
{
    QGridLayout *grid = new QGridLayout();

    grid->setHorizontalSpacing(0);
    grid->setVerticalSpacing(0);
    grid->setSpacing(0);
    grid->setAlignment(Qt::AlignHCenter);

    for(int i=0; i < rows; i++) {
        std::vector<GridCell*> row;
        cells.push_back(row);
        for(int j=0; j < cols; j++) {
			GridCell *cell = new GridCell(model->getLattice()->getElement(i,j),NULL, border);
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

	QPushButton*stepButton = new QPushButton("STEP");
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

	QPushButton *clearButton = new QPushButton("CLEAR");
    clearButton->setFixedSize(100,25); 
    connect(clearButton, SIGNAL(clicked()), this, SLOT(handleClear()));
    buttonRow->addWidget(clearButton);

	QPushButton *randomButton = new QPushButton("RANDOMIZE");
    clearButton->setFixedSize(100,25); 
    connect(randomButton, SIGNAL(clicked()), this, SLOT(handleRandom()));
    buttonRow->addWidget(randomButton);

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
	speed = s;
	if (running) {
		handlePause(); 
		handleStart(); 
	}
}

void GridWindow::handleStep() { 
	timerFired(); 
}

void GridWindow::handleStart() {
	running = true; 
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerFired()));
    this->timer->start(2000/speed);
}

void GridWindow::handlePause() {
		cout << "Simulation paused at step : " << steps << endl; 
		running = false; 
        this->timer->stop();
        delete this->timer;
}

void GridWindow::handleClear() {
	cout << "Clearing board "; 
	steps = 0; 
    for(unsigned int row=1; row < cells.size()-1; row++) {
		cout << "... "; 
        for(unsigned int col=1; col < cells[row].size()-1; col++) {
            GridCell *cell = cells[row][col];
            cell->setAndDraw(LatElem::Empty);
        }
    }
	cout << endl; 
	cout << "Step : " << steps << endl; 
}

void GridWindow::handleRandom(){
	handleClear();
	int p; 
	cout << "Please entere probability (1-100) with which cells should be filled :" << endl;
	cin >> p; 
	for(int i = 0; i < cells.size(); i++) { 
		for(int j = 0; j < cells[0].size(); j++) {
			cells[i][j]->set_random(p); 
		}
	}
}

void GridWindow::handleExport() {
	int filetype;
	string filename; 
	cout << "Choose filetype :" << endl; 
	cout << "0 : stl" << endl; 
	cout << "1 : ply" << endl; 
	cout << "2 : flow" << endl; 
	cin >> filetype; 
	cout << "Please enter filename :" << endl; 
	cin >> filename; 
	cout << "Constructing cube array ... ";
	CubeArray cArr(*model,3,true);
	cout << "done!" << endl; 
	cout << "Constructing polyhedron ... "; 
	Polyhedron poly(cArr, 0.0005, 1.0);
	cout << "done!" << endl; 
	cout << "Exporting geometry ... "; 
	switch(filetype) { 
	case 0:
		poly.print_stl(filename);
		break;
	case 1: 
		poly.print_ply(filename); 
	case 2: 
		break; 
	default: 
		break; 
	}
	cout << "done!" << endl; 
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

