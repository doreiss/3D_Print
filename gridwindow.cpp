#include <iostream>
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
	QHBoxLayout *counterBox = setupCounter(); 
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addLayout(header);
    layout->addLayout(grid);
    layout->addLayout(buttonRow);
	layout->addLayout(sliderBox); 
	layout->addLayout(counterBox); 
    setLayout(layout);
}

GridWindow::~GridWindow()
{
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

QHBoxLayout* GridWindow::setupCounter() { 
	QHBoxLayout *counterBox = new QHBoxLayout(); 
	counterBox->setAlignment(Qt::AlignLeft); 

	this->counter = new QTextEdit(); 
	counter->setText("Step: 0"); 

	counterBox->addWidget(counter); 

	return counterBox; 
}


QHBoxLayout* GridWindow::setupHeader()
{
    QHBoxLayout *header = new QHBoxLayout();
    header->setAlignment(Qt::AlignHCenter);

    this->title = new QLabel("LATTICE GAS",this);
    this->title->setAlignment(Qt::AlignHCenter);
    this->title->setFont(QFont("Arial", 25, QFont::Bold));

    header->addWidget(this->title);

    return header;
}

QGridLayout* GridWindow::setupGrid(int rows,int cols)
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
			GridCell *cell = new GridCell(model->getLattice()->getElement(i,j));
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

    QPushButton *quitButton = new QPushButton("EXIT");
    quitButton->setFixedSize(100,25); 
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttonRow->addWidget(quitButton);

	 QPushButton *clearButton = new QPushButton("CLEAR");
    clearButton->setFixedSize(100,25); 
    connect(clearButton, SIGNAL(clicked()), this, SLOT(handleClear()));
    buttonRow->addWidget(clearButton);

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
		running = false; 
        this->timer->stop();
        delete this->timer;
}

void GridWindow::handleClear() {
	steps = 0; 
    for(unsigned int row=1; row < cells.size()-1; row++) {
        for(unsigned int col=1; col < cells[row].size()-1; col++) {
            GridCell *cell = cells[row][col];
            cell->setAndDraw(0);
        }
    }
}

std::vector<std::vector<GridCell*> >& GridWindow::getCells() {
    return this->cells;
}


void GridWindow::timerFired() {
	steps++;
	QString stepDisplay = "Step: ";
	char buffer[33]; 
	itoa(steps,buffer,10); 
	QString st(buffer); 
	counter->setText(stepDisplay+st); 
	model->iterate();
	for(int m=0; m<cells.size(); m++)
	{
		for(int n=0; n<cells.at(m).size(); n++) {
			cells[m][n]->redrawCell();
		}
	}
}

