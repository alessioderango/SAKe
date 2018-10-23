//#pragma once
//#include "qcustomplot.h"
//#include <QMenu>
//#include <iostream>
//#include <boost/math/distributions/gamma.hpp>
//#include "Regression/parameters.h"


//using namespace std;
//class QCustomPlot;

//class CustomPlotRegression : public QQuickPaintedItem
//{
//    Q_OBJECT

//public:
//    CustomPlotRegression(double * kernel, int size_kernel,int number_of_function, QQuickItem* parent = 0 );
//    CustomPlotRegression(QQuickItem* parent = 0 );
//    virtual ~CustomPlotRegression();
//    void updateGraph0(QVector<double> x,QVector<double> y);
//    void updateGraph1(QVector<double> x,QVector<double> y);
//    void drawGammaFunctions(QVector<double> x, QVector<int> functionType, QVector<Parameters> parameter);

//    void paint( QPainter* painter );

//    Q_INVOKABLE void initCustomPlotRegression();



//    void setupQuadraticDemo(  double * kernely,
//                              int size_kernely,
//                              double * kernelx,
//                              int size_kernelx
//                              );


//    int getNumber_of_function() const;
//    void setNumber_of_function(int value);

//    std::vector<double> getX() const;
//    void setX(const std::vector<double> &x);

//protected:
//    void routeMouseEvents( QMouseEvent* event );

//    virtual void mousePressEvent( QMouseEvent* event );
//    virtual void mouseReleaseEvent( QMouseEvent* event );
//    virtual void mouseMoveEvent( QMouseEvent* event );
//    virtual void mouseDoubleClickEvent( QMouseEvent* event );
//    virtual void wheelEvent(QWheelEvent *event);
//    virtual void resizeEvent(QResizeEvent *event);


//private:
//  QCustomPlot*  m_CustomPlot;
//  int number_of_function;
//  std::vector<double> _x;
//  bool first_time;

//private slots:
//    void contextMenuRequest(QPoint pos);
//    void addRandomGraph();
//    void graphClicked( QCPAbstractPlottable* plottable );
//    void onCustomReplot();
//    void updateCustomPlotSize();

//};
