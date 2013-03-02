#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <QWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QTimer>
#include <QLineEdit>
#include <QGridLayout>
#include <QTextEdit>
#include <QSpinBox>
#include <QLabel>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>

#include "GasModel.h"
#include "gridwindow.h"

class GasOptions : public QWidget
{
    Q_OBJECT
	public:
		GasOptions(int r, int c, std::string n, QWidget *parent = NULL) {
			rows = r; 
			cols = c;
			name = n; 
			init();
		}
	public slots: 
		void handleProb(int state) {
			p = state; 
		}
		void handleApply(void) { 
			Lattice* l = new Lattice(rows,cols,LatElem::Full);
			QMainWindow *gridWindow = new QMainWindow();
			l->setSubLattice(1,rows - 2,1,cols - 2,LatElem::Empty);
			srand(time(NULL)); 
			for(int i = 0; i < l->rowSize(); ++i) { 
				for(int j = 0; j < l->colSize(); ++j) { 
					if(rand()%100 < p) { 
						l->setElement(i,j,LatElem::Full); 
					}
				} 
			}
			GasModel* g = new GasModel(*l);
			GridWindow* widget = new GridWindow(g,name,NULL);
			gridWindow->setCentralWidget(widget); 
			gridWindow->show();
			gridWindow->activateWindow();
			this->hide(); 
		}
	private:
		int rows; 
		int cols;
		int p;
		std::string name; 
		QSpinBox* prob; 
		bool initialRandom;
		void init(void) {
			QVBoxLayout *layout = new QVBoxLayout(); 
			QVBoxLayout *layout1 = new QVBoxLayout(); 
			
			QGroupBox *group = new QGroupBox(); 
			group->resize(300,300);
			group->setLayout(layout); 
			group->setAlignment(Qt::AlignHCenter); 
			group->setTitle("Gas Options"); 

			prob = new QSpinBox();   
			prob->setMinimum(0);  
			prob->setMaximum(100);
			p = 0; 

			QLabel *probLabel = new QLabel(tr("Initialize with probability p each cell to be full (p = 0 for clear board)"));
			
			layout->addWidget(probLabel); 
			layout->addWidget(prob);
			
			connect(prob,SIGNAL(valueChanged(int)),this,SLOT(handleProb(int))); 

			QPushButton* applyButton = new QPushButton("Apply");
			layout->addWidget(applyButton); 

			connect(applyButton,SIGNAL(clicked()),this,SLOT(handleApply(void))); 

			layout1->addWidget(group); 
			
			setLayout(layout1); 
		}
};