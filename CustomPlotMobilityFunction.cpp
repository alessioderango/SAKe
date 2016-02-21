#include "CustomPlotMobilityFunction.h"
using boost::posix_time::ptime;
using namespace boost::gregorian;
using namespace boost::posix_time;
#include <QDebug>

CustomPlotMobilityFunction::CustomPlotMobilityFunction( QQuickItem* parent ) : QQuickPaintedItem( parent )
    , m_CustomPlot( nullptr )
{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );



    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotMobilityFunction::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotMobilityFunction::updateCustomPlotSize );
}

CustomPlotMobilityFunction::~CustomPlotMobilityFunction()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotMobilityFunction::initCustomPlotMobilityFunction()
{
    m_CustomPlot = new QCustomPlot();

    updateCustomPlotSize();

    setupQuadraticDemo( m_CustomPlot );

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotMobilityFunction::onCustomReplot );

    m_CustomPlot->replot();
}


void CustomPlotMobilityFunction::paint( QPainter* painter )
{
    if (m_CustomPlot)
    {



        QPixmap    picture( boundingRect().width(),boundingRect().height());
        //QPixmap    picture( boundingRect().size().toSize());
        QCPPainter qcpPainter( &picture );

        //m_CustomPlot->replot();
        m_CustomPlot->toPainter( &qcpPainter );
        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotMobilityFunction::mousePressEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotMobilityFunction::mouseReleaseEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotMobilityFunction::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (m_CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeZoom(m_CustomPlot->xAxis->orientation());
  else if (m_CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeZoom(m_CustomPlot->yAxis->orientation());
  else
    m_CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void CustomPlotMobilityFunction::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (m_CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeDrag(m_CustomPlot->xAxis->orientation());
  else if (m_CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeDrag(m_CustomPlot->yAxis->orientation());
  else
    m_CustomPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}


void CustomPlotMobilityFunction::wheelEvent(QWheelEvent *event){
    double factor;
    double wheelSteps = event->delta()/120.0; // a single step delta is +/-120 usually
    factor = qPow(m_CustomPlot->axisRect()->rangeZoomFactor(Qt::Horizontal), wheelSteps);
    if (m_CustomPlot->axisRect()->rangeZoomAxis(Qt::Horizontal))
      m_CustomPlot->axisRect()->rangeZoomAxis(Qt::Horizontal)->scaleRange(factor,  m_CustomPlot->axisRect()->rangeZoomAxis(Qt::Horizontal)->pixelToCoord(event->pos().x()));
    factor = qPow(m_CustomPlot->axisRect()->rangeZoomFactor(Qt::Vertical), wheelSteps);
    if (m_CustomPlot->axisRect()->rangeZoomAxis(Qt::Vertical))
     m_CustomPlot->axisRect()->rangeZoomAxis(Qt::Vertical)->scaleRange(factor, m_CustomPlot->axisRect()->rangeZoomAxis(Qt::Vertical)->pixelToCoord(event->pos().y()));
    m_CustomPlot->replot();
    //cout <<"wheeeel" << endl;
}


void CustomPlotMobilityFunction::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotMobilityFunction::mouseDoubleClickEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotMobilityFunction::graphClicked( QCPAbstractPlottable* plottable )
{
    //qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotMobilityFunction::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
        m_CustomPlot->replot();
    }
}

void CustomPlotMobilityFunction::updateCustomPlotSize()
{

    if (m_CustomPlot)
    {
       // std::cout << " width() "<< width() << "  height() " << height() << std::endl;
       m_CustomPlot->setGeometry( 0, 0, width(), height() );
       m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}

void CustomPlotMobilityFunction::onCustomReplot()
{
    //qDebug() << Q_FUNC_INFO;
    update();
}

void CustomPlotMobilityFunction::setupQuadraticDemo( QCustomPlot* customPlot )
{

    // set locale to english, so we get english month names:
    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));

      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(0, 0, 255, 200));
      customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
      customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
      customPlot->yAxis->setRange( 0,20 );

      customPlot->addGraph();
      customPlot->graph( 1 )->setPen( QPen( Qt::gray ) );

      QVector<double> timetmp(rain_size),ytime(rain_size);
      for (int i=0; i<rain_size; i++){
          timetmp[i]=(ptime_from_tm(rain[i].getTime())-ptime(date(1970, Jan, 1))).total_seconds();
          ytime[i]=0;
      }

      customPlot->graph(1)->setData(timetmp, ytime);

      customPlot->addGraph();

      customPlot->graph(2)->setData(timetmp, ytime);

    //}
    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("dd\nMMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set a fixed tick-step to one tick per month:
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(2628000); // one month in seconds
   // customPlot->xAxis->setSubTickCount(3);
    // apply manual tick and tick label for left axis:
  //  customPlot->yAxis->setAutoTicks(false);
  //  customPlot->yAxis->setAutoTickLabels(false);
//    customPlot->yAxis->setTickVector(QVector<double>() << 5 << 55);
//    customPlot->yAxis->setTickVectorLabels(QVector<QString>() << "Not so\nhigh" << "Very\nhigh");
    // set axis labels:
    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("y");
    // make top and right axes visible but without ticks and labels:
//    customPlot->xAxis2->setVisible(true);
//    customPlot->yAxis2->setVisible(true);
//    customPlot->xAxis2->setTicks(false);
//    customPlot->yAxis2->setTicks(false);
//    customPlot->xAxis2->setTickLabels(false);
//    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:


     ptime rain0 = ptime_from_tm(rain[0].getTime());
     ptime rainLast = ptime_from_tm(rain[rain_size-1].getTime());
     boost::posix_time::time_duration diff1 =(rain0-ptime(date(1970, Jan, 1)));
     boost::posix_time::time_duration diff2 = (rainLast-ptime(date(1970, Jan, 1)));
//      cout << diff1.total_seconds()<< " "<<diff2.total_seconds() << endl;

     customPlot->xAxis->setRange(diff1.total_seconds(), diff2.total_seconds());
     customPlot->yAxis->setRange( 0, 20 );


    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    first = true;
    int graphnum=3;
    if(first){
      QVector<double> x(100), y(100);
      for (int j=0; j<activation_size; j++)
     {     tm a1=activation[j].getStart();
          //a1.tm_mday-=1;
          //cout << a1.tm_mday<< " "<<a1.tm_mon<< " "<<a1.tm_year << endl;
          tm a2=activation[j].getEnd();
          // cout << a1.tm_mday<< " "<<a1.tm_mon<< " "<<a1.tm_year<< endl;
          //a2.tm_mday+=2;
          for (int k=0; k<2; k++)
            {
              customPlot->addGraph();
               for (int i=0; i<(int)100; i++)
                {

                   if(k%2==0){

                        customPlot->graph( graphnum )->setPen( QPen( Qt::green) );

                        ptime tmp1 = ptime_from_tm(a1);
                        //ptime t11 = local_adj::utc_to_local(tmp1);

                        ptime utcepoch = ptime(date(1970, Jan, 1));
                        //ptime utcepoch1 = local_adj::utc_to_local(utcepoch);
                        //std::cout << (raindate-ptime(date(1970, Jan, 1))).total_milliseconds() << "\n";
                        boost::posix_time::time_duration diff =(tmp1-utcepoch);
                        //diff.total_milliseconds();
                        x[i] = diff.total_seconds();
                   }else{

                        customPlot->graph( graphnum )->setPen( QPen( Qt::blue) );
                        ptime tmp2 = ptime_from_tm(a2);
                        x[i] =(tmp2-ptime(date(1970, Jan, 1))).total_seconds();
                   }
                   y[i] = i;

                   //cout << x[i] << " "<< y[i]  << endl;
                }

               customPlot->graph(graphnum)->setData(x, y);
              // customPlot->graph(graphnum)->rescaleAxes(true);
               graphnum++;
          }


       }
      first =false;

    }


    customPlot->replot();
    //cout << max << endl;

}

void CustomPlotMobilityFunction::setActivation(Activation *value,int _activation_size)
{
    activation = value;
    activation_size=_activation_size;
}

Rain *CustomPlotMobilityFunction::getRain() const
{
    return rain;
}

void CustomPlotMobilityFunction::setRain(Rain *value,int _rain_size)
{
    rain = value;
    rain_size =_rain_size;
}

void CustomPlotMobilityFunction::updateGraph(double *Y,double YsMin,double YsMin2){




    m_CustomPlot->graph( 0 )->setPen( QPen( Qt::red ) );
//    qDebug() << "aggiorno" << endl;
    double max =-1;
    QVector<double> time(rain_size), value(rain_size);
    for (int i=0; i<rain_size; i++)
    {
     // qDebug() << mktime(&(rain[i].getTime()));
     // boost::posix_time::time_duration diff1 =(rain0-ptime(date(1970, Jan, 1)));
      ptime raintime = ptime_from_tm(rain[i].getTime());
      boost::posix_time::time_duration diff =(raintime-ptime(date(1970, Jan, 1)));
      time[i] = diff.total_seconds();
      value[i]=Y[i];
        if(value[i] > max)
            max=value[i];
    }

    m_CustomPlot->graph(0)->setData(time, value);
    //m_CustomPlot->yAxis->setRange( 0,max );



    QVector<double> timetmp(rain_size),ytime(rain_size),ytime2(rain_size);
    for (int i=0; i<rain_size; i++){
        timetmp[i]=(ptime_from_tm(rain[i].getTime())-ptime(date(1970, Jan, 1))).total_seconds();
        ytime[i]=YsMin;
        ytime2[i]=YsMin2;
    }
//    m_CustomPlot->graph(1)->setLineStyle((QCPGraph::LineStyle)0);
    m_CustomPlot->graph(1)->setData(timetmp, ytime);
    m_CustomPlot->graph(2)->setData(timetmp, ytime2);

//     m_CustomPlot->addGraph();
//       pen.setColor(QColor(qSin(1+1.2)*80+80, qSin(0.3+0)*80+80, qSin(0.3+1.5)*80+80));
//       m_CustomPlot->graph(1)->setPen(pen);
//       m_CustomPlot->graph(1)->setName(lineNames.at(QCPGraph::lsNone));
//       m_CustomPlot->graph(1)->setLineStyle((QCPGraph::LineStyle));
//       m_CustomPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

//       // generate data:
//       QVector<double> x(15), y(15);
//       for (int j=0; j<activation_size; j++)
//       {
//         x[j] = activation[j].;
//         y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
//       }
//       m_CustomPlot->graph(1)->setData(x, y);
//       m_CustomPlot->graph(1)->rescaleAxes(true);

     /* m_CustomPlot->graph(1)->setData(x, y);
      m_CustomPlot->graph(1)->rescaleAxes(true);
   m_CustomPlot->replot();*/

    m_CustomPlot->replot();


}

void CustomPlotMobilityFunction::updateGraph1(QVector<double> x,QVector<double> y){


    if(x.size() > 20)
          m_CustomPlot->xAxis->setRange( 0, x.size() );
     m_CustomPlot->graph( 1 )->setData( x, y);



     m_CustomPlot->replot();

}


void CustomPlotMobilityFunction::resizeEvent(QResizeEvent *event)
{
//    cout << "CustomPlotMobilityFunction " << endl;
    m_CustomPlot->resize(event->size());
}
