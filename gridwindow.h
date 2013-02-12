#pragma once

#include <vector>
#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include <QTextEdit>
#include <QSlider>
#include <QLabel>
#include <QApplication>
#include <sstream>
#include <string>
#include "gridcell.h"
#include "Gas.h"
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
		Gas *model;
		int steps;
		int speed;
		bool running;


    public slots:
		void handleStep(void);
        void handleStart(void);
        void handlePause(void);
		void handleClear(void);
		void handleSlider(int);
		void handleRandom(void);
		void handleExport(void); 
        void timerFired(void);

    public:
        GridWindow(Gas&,QWidget *parent = NULL);
        virtual ~GridWindow();
        std::vector<std::vector<GridCell*> >& getCells();

    private:
		void ChangeModel(Gas&,bool); 
        QHBoxLayout* setupHeader(void);
        QGridLayout* setupGrid(int rows,int cols, bool = true);
        QHBoxLayout* setupButtonRow(void);
		QHBoxLayout* setupSlider(void);

		string convertInt(int); 
};