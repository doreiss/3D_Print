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

#include "FireModel.h"
#include "gridwindow.h"

class FireOptions : public QWidget
{
    Q_OBJECT
	public:
		FireOptions(int r, int c, std::string n, QWidget *parent = NULL) {
			rows = r; 
			cols = c;
			name = n; 
			init();
		}
	public slots: 
		void handleProb(int state) {
			p = state; 
		}
		void handleGRate(int state) { 
			growthRate = state; 
		}
		void handleLRate(int state) { 
			lightningRate = state; 
		}
		void handleBRate(int state) { 
			burningRate = state; 
		}
		void handleBTime(int state) { 
			burningTime = state; 
		}
		void handleApply(void) { 
			Lattice* l = new Lattice(rows,cols,LatElem::Empty);
			QMainWindow *gridWindow = new QMainWindow();
			srand(time(NULL)); 
			for(int i = 0; i < l->rowSize(); ++i) { 
				for(int j = 0; j < l->colSize(); ++j) { 
					if(rand()%100 < p) { 
						l->setElement(i,j,LatElem::Full); 
					}
				} 
			}
			FireModel* g = new FireModel(*l,growthRate,lightningRate,burningRate,burningTime);
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
		int growthRate; 
		int lightningRate; 
		int burningRate; 
		int burningTime; 

		std::string name;

		QSpinBox* prob;
		QSpinBox* gRate;
		QSpinBox* lRate; 
		QSpinBox* bRate;
		QSpinBox* bTime;

		void init(void) {
			QVBoxLayout *layout = new QVBoxLayout(); 
			QVBoxLayout *layout1 = new QVBoxLayout(); 
			
			QGroupBox *group = new QGroupBox(); 
			group->resize(300,300);
			group->setLayout(layout); 
			group->setAlignment(Qt::AlignHCenter); 
			group->setTitle("Fire Options"); 

			prob = new QSpinBox();   
			prob->setMinimum(0);  
			prob->setMaximum(100);
			p = 0; 
			QLabel *probLabel = new QLabel(tr("Initialize with probability p each cell to be full (p = 0 for clear board)"));
			layout->addWidget(probLabel); 
			layout->addWidget(prob);
			connect(prob,SIGNAL(valueChanged(int)),this,SLOT(handleProb(int))); 

			gRate = new QSpinBox();   
			lRate = new QSpinBox();   
			bRate = new QSpinBox();   
			bTime = new QSpinBox();   
			
			gRate->setMinimum(0);  
			gRate->setMaximum(100);
			lRate->setMinimum(0);  
			lRate->setMaximum(100);
			bRate->setMinimum(0);  
			bRate->setMaximum(100);
			bTime->setMinimum(0);  
			bTime->setMaximum(10);
			
			growthRate = 0; 
		    lightningRate = 0; 
		    burningRate = 0; 
		    burningTime = 0; 

			QLabel *growthLabel = new QLabel(tr("Growth Chance"));
			QLabel *lightningLabel = new QLabel(tr("Lightning Strike Chance"));
			QLabel *burningRLabel = new QLabel(tr("Burning Chance"));
			QLabel *burningTLabel = new QLabel(tr("Burning Time"));
			
			layout->addWidget(growthLabel); 
			layout->addWidget(gRate);
			layout->addWidget(lightningLabel); 
			layout->addWidget(lRate); 
			layout->addWidget(burningRLabel); 
			layout->addWidget(bRate); 
			layout->addWidget(burningTLabel); 
			layout->addWidget(bTime); 

			connect(gRate,SIGNAL(valueChanged(int)),this,SLOT(handleGRate(int)));
			connect(lRate,SIGNAL(valueChanged(int)),this,SLOT(handleLRate(int)));
			connect(bRate,SIGNAL(valueChanged(int)),this,SLOT(handleBRate(int)));
			connect(bTime,SIGNAL(valueChanged(int)),this,SLOT(handleBTime(int)));
			
			QPushButton* applyButton = new QPushButton("Apply");
			layout->addWidget(applyButton); 

			connect(applyButton,SIGNAL(clicked()),this,SLOT(handleApply(void))); 

			layout1->addWidget(group); 
			
			setLayout(layout1); 
		}
};