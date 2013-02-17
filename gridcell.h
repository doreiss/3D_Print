#pragma once

#include <QPalette>
#include <QColor>
#include <QPushButton>
#include <Qt>
#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <iostream>
#include "LatElem.h"

class GridCell : public QFrame {
    Q_OBJECT

    private:
        QPushButton* button;
		LatElem* elem;
		bool bordered;

    public slots:
		void setAndDraw(LatElem::LatType);
		void handleClick();

    signals:
       void typeChanged(int val);

    public:
        GridCell(LatElem* fromModel,QWidget *parent = NULL, bool = true);
		void set_random(int); 
        virtual ~GridCell();
        void redrawCell();

    private:
        Qt::GlobalColor getColorForCellType();
};