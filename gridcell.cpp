#include <iostream>

#include "gridcell.h"

using namespace std;

GridCell::GridCell(LatElem* fromModel, QWidget *parent)
: QFrame(parent)
{  
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

void GridCell::setAndDraw(int val) {
    elem->setValue(val); 
    redrawCell();
}

Qt::GlobalColor GridCell::getColorForCellType()
{
    switch(this->elem->getValue())
    {
        case 0:
            return Qt::white;
        case 1:
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
	int newval = (elem->getValue() == 1 ? 0 : 1);
	setAndDraw(newval);
}

void GridCell::redrawCell() {
    Qt::GlobalColor gc = getColorForCellType();
    this->button->setPalette(QPalette(gc,gc));
    this->button->setAutoFillBackground(true);
    this->button->setFlat(true);
}