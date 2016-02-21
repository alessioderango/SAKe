#pragma once
#include "qcustomplot.h"
#include <QtQuick>
#include <iostream>


using namespace std;
class QCustomPlot;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotItem( QQuickItem* parent = 0 );
    virtual ~CustomPlotItem();
    void updateGraph1(QVector<double> x,QVector<double> y);
    void paint( QPainter* painter );

    void updateGraph0(QVector<double> x,QVector<double> y);
    Q_INVOKABLE void initCustomPlotFitness();

protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    void setupQuadraticDemo( QCustomPlot* customPlot );

private:
  QCustomPlot*  m_CustomPlot;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();

};
