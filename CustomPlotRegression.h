#pragma once
#include "qcustomplot.h"
#include <QtQuick>
#include <iostream>


using namespace std;
class QCustomPlot;

class CustomPlotRegression : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotRegression(double * kernel, int size_kernel, QQuickItem* parent = 0 );
    CustomPlotRegression(QQuickItem* parent = 0 );
    virtual ~CustomPlotRegression();
    void updateGraph0(QVector<double> x,QVector<double> y);
    void updateGraph1(QVector<double> x,QVector<double> y);
    void paint( QPainter* painter );

    Q_INVOKABLE void initCustomPlotRegression();



    void setupQuadraticDemo(  double * kernely,
                              int size_kernely,
                              double * kernelx,
                              int size_kernelx
                              );


protected:
    void routeMouseEvents( QMouseEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent(QResizeEvent *event);


private:
  QCustomPlot*  m_CustomPlot;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();

};
