#pragma once
#include "qcustomplot.h"
#include <QtQuick>
#include <iostream>
using namespace std;
class QCustomPlot;

class CustomPlotKernel : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotKernel( QQuickItem* parent = 0 );
    virtual ~CustomPlotKernel();
    void updateGraph1(QVector<double> x,QVector<double> y);
    void paint( QPainter* painter );

    void updateGraph(double* x,int y) const;
    Q_INVOKABLE void initCustomPlotFitness();

protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void resizeEvent(QResizeEvent *event);
    void setupQuadraticDemo( QCustomPlot* customPlot );

private:
  QCustomPlot*  m_CustomPlot;
   QCPBars *myBars;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();
    void mouseWheel();
    void mousePress();

};
