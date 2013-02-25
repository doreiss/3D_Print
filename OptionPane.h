#pragma once

#include <iostream>
#include <string>
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

#include "gridwindow.h"
#include "gridcell.h"
#include "Model.h"
#include "FireModel.h"
#include "GasModel.h"

class OptionPane : public QWidget
{
    Q_OBJECT

	public:
		OptionPane(QWidget *parent = NULL) {
			init();
			
		}
		std::string getName(void) { 
			return name; 
		}
		int getRows(void) { 
			return rows; 
		}
		int getCols(void) { 
			return cols; 
		}
		bool isGas(void) { 
			return latticeTypeBool; 
		}
	public slots: 
		void handleLatCheck(void) { 
			latticeTypeBool = !latticeTypeBool;
		}
		void handleRows(int r) {
			rows = r;	
		}
		void handleCols(int c) { 
			cols = c; 
		}
		void handleName(QString s) { 
			name = s.toStdString();
		}
		void handleApply(void) {
			Lattice* l = new Lattice(rows,cols,LatElem::Full);
			QMainWindow *gridWindow = new QMainWindow();
			
			if(latticeTypeBool) {
				l->setSubLattice(0,rows-1,0,cols-1,LatElem::Full); 
				l->setSubLattice(1,rows - 2,1,cols - 2,LatElem::Empty);
				GasModel* g = new GasModel(*l);
				GridWindow* widget = new GridWindow(g,name,NULL);
				gridWindow->setCentralWidget(widget); 
				gridWindow->show();
				gridWindow->activateWindow(); 
			}
			else{ 
				l->setSubLattice(0,rows-1,0,cols-1,LatElem::Empty); 
				FireModel* f = new FireModel(*l); 
				GridWindow* widget = new GridWindow(f,name,NULL);
				gridWindow->setCentralWidget(widget); 
				gridWindow->show();
				gridWindow->activateWindow(); 
			}
			this->hide();
		}
	private:
		bool latticeTypeBool;
		int rows; 
		int cols;
		std::string name; 
		void init(void) { 
			QVBoxLayout *layout = new QVBoxLayout(); 
			QVBoxLayout *layout1 = new QVBoxLayout(); 
			
			QGroupBox *group = new QGroupBox(); 
			group->resize(300,300);
			group->setLayout(layout); 
			group->setAlignment(Qt::AlignHCenter); 
			group->setTitle("Init Options"); 

			QCheckBox* latticeType = new QCheckBox("Gas (check) / Fire");
			latticeTypeBool = false; 

			layout->addWidget(latticeType);
			connect(latticeType,SIGNAL(stateChanged(int)),this,SLOT(handleLatCheck())); 

			QSpinBox* noRows = new QSpinBox(); 
			QSpinBox* noCols = new QSpinBox(); 
			noRows->setMinimum(1); 
			noCols->setMinimum(1); 
			noRows->setMaximum(100); 
			noCols->setMaximum(100);
			rows = 1; 
			cols = 1; 

			QLabel *rowLabel = new QLabel(tr("Row:"));
			QLabel *colLabel = new QLabel(tr("Col:"));

			layout->addWidget(rowLabel); 
			layout->addWidget(noRows);
			layout->addWidget(colLabel); 
			layout->addWidget(noCols); 
			
			connect(noRows,SIGNAL(valueChanged(int)),this,SLOT(handleRows(int))); 
			connect(noCols,SIGNAL(valueChanged(int)),this,SLOT(handleCols(int))); 

			QLabel *nameLabel = new QLabel(tr("Object Name:")); 
			QLineEdit *nameLine = new QLineEdit(); 
			name = ""; 

			layout->addWidget(nameLabel); 
			layout->addWidget(nameLine); 

			connect(nameLine,SIGNAL(textChanged(QString)),this,SLOT(handleName(QString)));

			QPushButton* applyButton = new QPushButton("Apply");
			layout->addWidget(applyButton); 

			connect(applyButton,SIGNAL(clicked()),this,SLOT(handleApply(void))); 

			layout1->addWidget(group); 
			
			setLayout(layout1); 
		}
};