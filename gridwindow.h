#pragma once

#include <vector>
#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include <QTextEdit>
#include <QSlider>
#include <QLabel>
#include <QApplication>
#include <QDialog>
#include <sstream>
#include <string>
#include "gridcell.h"
#include "Model.h"
#include "CubeArray.h"
#include "Polyhedron.h"

class GridWindow : public QWidget
{
    Q_OBJECT

    private:
        std::vector< std::vector< GridCell* > > cells;
        QLabel *title;
		QTextEdit *counter; 
        QTimer *timer;
		Model *model;
		int steps;
		int speed;
		bool running;
		bool init; 
		std::string name; 

    public slots:
		void handleStep(void);
        void handleStart(void);
        void handlePause(void);
		void handleSlider(int);
		void handleExport(void); 
        void timerFired(void);

    public:
        GridWindow(Model*,std::string,QWidget *parent = NULL);
        virtual ~GridWindow(void);
        std::vector<std::vector<GridCell*> >& getCells();

    private:
        QHBoxLayout* setupHeader(void);
        QGridLayout* setupGrid(int rows,int cols);
        QHBoxLayout* setupButtonRow(void);
		QHBoxLayout* setupSlider(void);
		void exitSetup(void); 

		string convertInt(int);
};