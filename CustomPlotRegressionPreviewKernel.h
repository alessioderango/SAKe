#pragma once
#include "qcustomplot.h"
#include <QtQuick>
#include <iostream>
#include "controlpoints.h"


using namespace std;
class QCustomPlot;

class CustomPlotRegressionPreviewKernel : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotRegressionPreviewKernel(double * kernel, int size_kernel, QQuickItem* parent = 0 );
    CustomPlotRegressionPreviewKernel(QQuickItem* parent = 0 );
    virtual ~CustomPlotRegressionPreviewKernel();
    void updateGraph0(QVector<double> x,QVector<double> y);
    void updateGraph1(QVector<double> x,QVector<double> y);
    void updateGraph(double* Fi,int tb) const;
    void paint( QPainter* painter );

    Q_INVOKABLE void initCustomPlotRegressionPreviewKernel();
    Q_INVOKABLE void initCustomPlotRegressionPreviewKernel(const QVariant& filename);
    Q_INVOKABLE void initCustomPlotKernelComtrolPoints(const QVariant& filename);


    void setupQuadraticDemo(QCustomPlot* m);


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
  QCPBars *myBars;
private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();

};
