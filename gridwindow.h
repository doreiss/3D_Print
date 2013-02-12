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

class GridWindow : public QWidget
{
    Q_OBJECT

    private:
        std::vector<std::vector<GridCell*> > cells;
        QLabel *title;
		QTextEdit *counter; 
        QTimer *timer;
		Gas *model;
		int steps;
		int speed;
		bool running; 

    public slots:
		void handleStep();
        void handleStart();
        void handlePause();
		void handleClear();
		void handleSlider(int); 
        void timerFired();

    public:
        GridWindow(Gas&,QWidget *parent = NULL);
        virtual ~GridWindow();
        std::vector<std::vector<GridCell*> >& getCells();

    private:
        QHBoxLayout* setupHeader();
        QGridLayout* setupGrid(int rows,int cols);
        QHBoxLayout* setupButtonRow();
		QHBoxLayout* setupSlider();
		QHBoxLayout* setupCounter(); 

		string convertInt(int); 
};