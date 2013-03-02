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

#include "GasOptions.h"
#include "FireOptions.h"

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
	public slots: 
		void handleGasCheck(int state) { 
			isGas = (state == 2);
			if(isGas) { 
				latticeDGas->setCheckState(Qt::Unchecked); 
				latticeFire->setCheckState(Qt::Unchecked); 
			}
		}
		void handleDGasCheck(int state) { 
			isDGas = (state == 2);
			if(isDGas) {
				latticeGas->setCheckState(Qt::Unchecked); 
				latticeFire->setCheckState(Qt::Unchecked);
			}
		}
		void handleFireCheck(int state) {
			isFire = (state == 2); 
			if(isFire) { 
				latticeGas->setCheckState(Qt::Unchecked); 
				latticeDGas->setCheckState(Qt::Unchecked); 
			}
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
			QMainWindow *optionWindow = new QMainWindow();
			if(isGas) {
				GasOptions* widget = new GasOptions(rows,cols,name,NULL);
				optionWindow->setCentralWidget(widget);
			}
			else if (isFire) {
				FireOptions* widget = new FireOptions(rows,cols,name,NULL); 
				optionWindow->setCentralWidget(widget); 
			}
			else if (isDGas) {
			}
			optionWindow->show(); 
			optionWindow->activateWindow(); 
			this->hide();
		}
	private:
		bool isGas;
		bool isDGas; 
		bool isFire;
		QCheckBox* latticeGas; 
		QCheckBox* latticeDGas; 
		QCheckBox* latticeFire; 
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

			latticeGas = new QCheckBox("Gas"); 
			isGas = false; 

			latticeDGas = new QCheckBox("DGas");
			isDGas = false; 

			latticeFire = new QCheckBox("Fire"); 
			isFire = false; 

			layout->addWidget(latticeGas);
			connect(latticeGas,SIGNAL(stateChanged(int)),this,SLOT(handleGasCheck(int))); 

			layout->addWidget(latticeDGas);
			connect(latticeDGas,SIGNAL(stateChanged(int)),this,SLOT(handleDGasCheck(int))); 

			layout->addWidget(latticeFire);
			connect(latticeFire,SIGNAL(stateChanged(int)),this,SLOT(handleFireCheck(int))); 

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