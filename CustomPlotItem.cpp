#include "CustomPlotItem.h"

#include <QDebug>

CustomPlotItem::CustomPlotItem( QQuickItem* parent ) : QQuickPaintedItem( parent )
    , m_CustomPlot( nullptr )
{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );



    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotItem::initCustomPlotFitness()
{
    m_CustomPlot = new QCustomPlot();
    //m_CustomPlot->setMinimumHeight(200);
    updateCustomPlotSize();

    setupQuadraticDemo( m_CustomPlot );

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );

    m_CustomPlot->replot();
}


void CustomPlotItem::paint( QPainter* painter )
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

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::graphClicked( QCPAbstractPlottable* plottable )
{
    //qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
         m_CustomPlot->replot();
    }
}

void CustomPlotItem::wheelEvent(QWheelEvent *event){
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

void CustomPlotItem::updateCustomPlotSize()
{

    if (m_CustomPlot)
    {
       // std::cout << " width() "<< width() << "  height() " << height() << std::endl;
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}

void CustomPlotItem::onCustomReplot()
{
    //qDebug() << Q_FUNC_INFO;
    update();
}

void CustomPlotItem::setupQuadraticDemo( QCustomPlot* customPlot )
{
    // make top right axes clones of bottom left axes:
    QCPAxisRect* axisRect = customPlot->axisRect();

    // generate some data:
      QVector<double> x1( 0 ), y1( 0 );   // initialize with entries 0..100
//   QVector<double> lx( 101 ), ly( 101 ); // initialize with entries 0..100
//    for (int i = 0; i < 101; ++i)
//    {
//        x[i] = i / 50.0 - 1;              // x goes from -1 to 1
//        y[i] = x[i] * x[i];               // let's plot a quadratic function

//        lx[i] = i / 50.0 - 1;             //
//        ly[i] = lx[i];                    // linear
//    }
//    for (int i = 0; i < 101; ++i)
//    {
//        this->x[i] = i;              // x goes from -1 to 1
//        this->y[i] = i;               // let's plot a quadratic function

//   //     lx[i] = i / 50.0 - 1;             //
//   //     ly[i] = lx[i];                    // linear
//    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 0 )->setData( x1, y1 );

    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::green ) );
    customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 1 )->setData( x1, y1 );

    // give the axes some labels:
    customPlot->xAxis->setLabel( "Generation" );
    customPlot->yAxis->setLabel( "Fitness" );
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange( 0, 20 );
    customPlot->yAxis->setRange( 0, 1.05 );

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
}

 void CustomPlotItem::updateGraph0(QVector<double> x,QVector<double> y){

//     qDebug() << "aggiorno" << endl;

     if(x.size() > 20)
           m_CustomPlot->xAxis->setRange( 0, x.size() );
     m_CustomPlot->graph( 0 )->setData( x, y);
     m_CustomPlot->replot();


}

void CustomPlotItem::updateGraph1(QVector<double> x,QVector<double> y){


    if(x.size() > 20)
          m_CustomPlot->xAxis->setRange( 0, x.size() );
     m_CustomPlot->graph( 1 )->setData( x, y);
     m_CustomPlot->replot();


}


void CustomPlotItem::resizeEvent(QResizeEvent *event)
{
//    qDebug() << "CustomPlotItem " << endl;
    m_CustomPlot->resize(event->size());
}
