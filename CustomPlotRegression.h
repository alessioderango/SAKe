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
    void updateGraph1(QVector<double> x,QVector<double> y);
    void paint( QPainter* painter );

    void updateGraph0(QVector<double> x,QVector<double> y);
    Q_INVOKABLE void initCustomPlotFitness();



    void setupQuadraticDemo();

    double *getKernely() const;
    void setKernely(double *value);

    int getSize_kernely() const;
    void setSize_kernely(int value);

    double *getKernelx() const;
    void setKernelx(double *value);

    int getSize_kernelx() const;
    void setSize_kernelx(int value);

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
  double * kernely;
  int size_kernely;
  double * kernelx;
  int size_kernelx;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();

};
