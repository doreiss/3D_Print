#include <iostream>
#include <ctime>

#include "gridcell.h"

using namespace std;

GridCell::GridCell(LatElem* fromModel, QWidget *parent)
: QFrame(parent)
{
	off = false; 
	elem = fromModel; 
	setFrameStyle(QFrame::Box);
    this->button = new QPushButton(this);
    this->button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->button->setMinimumSize(19,19);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(this->button);
    setLayout(layout);

    layout->setStretchFactor(this->button,1);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
	connect(this->button,SIGNAL(clicked()),this,SLOT(handleClick()));
    redrawCell();
}

GridCell::~GridCell() {
    delete this->button;
}

void GridCell::setAndDraw(LatElem::LatType val) {
    elem->setValue(val); 
    redrawCell();
}

void GridCell::set_random(int p) {
	int ptest = rand() % 100;  
	if (ptest < p) setAndDraw(LatElem::Full);  
}

Qt::GlobalColor GridCell::getColorForCellType()
{
    switch(this->elem->getValue())
    {
	case LatElem::Empty:
            return Qt::white;
	case LatElem::Full:
			for(int i = 0; i < 8 ; i++) { 
				if(this->elem->getNeighbour(i) == NULL){ 
					return Qt::gray; 
				}
			}
            return Qt::cyan;
		default: 
			return Qt::black; 
    }
}

void GridCell::handleClick() {
	if(!off){
		LatElem::LatType newval = (elem->getValue() == LatElem::Full ? LatElem::Empty : LatElem::Full);
		setAndDraw(newval);
	}
}

void GridCell::redrawCell() {
    Qt::GlobalColor gc = getColorForCellType();
    this->button->setPalette(QPalette(gc,gc));
    this->button->setAutoFillBackground(true);
    this->button->setFlat(true);
}