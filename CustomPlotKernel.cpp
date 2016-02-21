#include "CustomPlotKernel.h"

#include <QDebug>

CustomPlotKernel::CustomPlotKernel( QQuickItem* parent ) : QQuickPaintedItem( parent )
    , m_CustomPlot( nullptr )
{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );



    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotKernel::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotKernel::updateCustomPlotSize );
}

CustomPlotKernel::~CustomPlotKernel()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotKernel::initCustomPlotFitness()
{
    m_CustomPlot = new QCustomPlot();
   // m_CustomPlot->setMaximumHeight(200);
    updateCustomPlotSize();

    setupQuadraticDemo( m_CustomPlot );

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotKernel::onCustomReplot );

    m_CustomPlot->replot();
}


void CustomPlotKernel::paint( QPainter* painter )
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

void CustomPlotKernel::mousePressEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}
//void CustomPlotKernel::mouseWheel( QMouseEvent* event )
//{
//    event->accept();
//    qDebug() << "entrato  mouseWheel";
//    qDebug() << Q_FUNC_INFO;
//    routeMouseEvents( event );

//    if (m_CustomPlot)
//    {
//        qDebug() << "entrato  mouseWheel";
//        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
//        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
//        QCoreApplication::postEvent( m_CustomPlot, newEvent );
//qDebug() << "entrato 1";
//        m_CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);

//    }

//}

void CustomPlotKernel::mouseReleaseEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotKernel::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotKernel::mouseDoubleClickEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotKernel::graphClicked( QCPAbstractPlottable* plottable )
{
    //qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotKernel::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );

        // m_CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
        //qDebug() << "entrato routeMouseEvents";
        m_CustomPlot->replot();

    }
}

void CustomPlotKernel::updateCustomPlotSize()
{

    if (m_CustomPlot)
    {
       // std::cout << " width() "<< width() << "  height() " << height() << std::endl;
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));

    }
}

void CustomPlotKernel::onCustomReplot()
{
    //qDebug() << Q_FUNC_INFO;
    update();
}

void CustomPlotKernel::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed
//    qDebug() << "entrato mouseWheel";
  if (m_CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeZoom(m_CustomPlot->xAxis->orientation());
  else if (m_CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeZoom(m_CustomPlot->yAxis->orientation());
  else
    m_CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}



void CustomPlotKernel::mousePress()
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

void CustomPlotKernel::setupQuadraticDemo( QCustomPlot* customPlot )
{


    myBars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(myBars);
    // now we can modify properties of myBars:
    myBars->setName("Bars Series 1");
//    QVector<double> keyData;
//    QVector<double> valueData;
//    keyData << 1 << 2 << 3<<4<<5<<6<<7<<8<<9<<10<<11<<12<<13;
//    valueData << 2 << 4 << 8 << 2 << 3<<4<<5 <<7 << 10 << 6 <<2 <<1<<9;
//    myBars->setData(keyData, valueData);
    customPlot->xAxis->setLabel("kernel");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange( 0,180 );
    customPlot->yAxis->setRange( -0.01,0.25 );
   // customPlot->rescaleAxes();

   // customPlot->replot();

//    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
//    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
//    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
//    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
}

 void CustomPlotKernel::updateGraph(double* Fi,int tb) const{

//     qDebug() << "aggiorno" << endl;
    QVector<double> keyData;
     QVector<double> valueData;
     for (int i = 0; i < tb; i++) {
         keyData.push_back(i);
         valueData.push_back(Fi[i]);
     }
     myBars->setData(keyData, valueData);
     //m_CustomPlot->rescaleAxes();
     m_CustomPlot->replot();


}

void CustomPlotKernel::updateGraph1(QVector<double> x,QVector<double> y){

    if(x.size() > 20)
          m_CustomPlot->xAxis->setRange( 0, x.size() );
     m_CustomPlot->graph( 1 )->setData( x, y);
     m_CustomPlot->replot();

}

void CustomPlotKernel::resizeEvent(QResizeEvent *event)
{
//    qDebug() << "CustomPlotKernel " << endl;
    m_CustomPlot->resize(event->size());
}
