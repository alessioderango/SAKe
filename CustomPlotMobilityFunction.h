#pragma once
#include "qcustomplot.h"
#include "SAke/Rain.h"
#include "SAke/Activation.h"
#include "SAke/Ym.h"
#include <QtQuick>
#include <time.h>
#include <iostream>
#include <qapplication.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"

using namespace std;
using namespace boost::posix_time;
using namespace std;
class QCustomPlot;

class CustomPlotMobilityFunction : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotMobilityFunction(QQuickItem* parent = 0 );
    virtual ~CustomPlotMobilityFunction();
    void updateGraph1(QVector<double> x,QVector<double> y);
    void paint( QPainter* painter );

    void updateGraph(double *Y,Ym YsMin,Ym YsMin2);
    Q_INVOKABLE void initCustomPlotMobilityFunction();

    Rain *getRain() const;
    void setRain(Rain *value,int _rain_size);

   void setActivation(Activation *value,int activate_size);

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
  Rain * rain;
  int rain_size;
  Activation * activation;
  int activation_size;
  bool first;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();
    void mouseWheel();
    void mousePress();

};
