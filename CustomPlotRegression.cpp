#include "CustomPlotRegression.h"

#include <QDebug>

CustomPlotRegression::CustomPlotRegression(QQuickItem* parent ) : QQuickPaintedItem( parent )
  , m_CustomPlot( nullptr )
{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );

    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotRegression::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotRegression::updateCustomPlotSize );
}

CustomPlotRegression::~CustomPlotRegression()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotRegression::initCustomPlotRegression()
{
    m_CustomPlot = new QCustomPlot();
    //m_CustomPlot->setMinimumHeight(200);
    updateCustomPlotSize();

//    setupQuadraticDemo( m_CustomPlot );

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotRegression::onCustomReplot );

    m_CustomPlot->replot();
}


void CustomPlotRegression::paint( QPainter* painter )
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

void CustomPlotRegression::mousePressEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotRegression::mouseReleaseEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotRegression::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotRegression::mouseDoubleClickEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotRegression::graphClicked( QCPAbstractPlottable* plottable )
{
    //qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotRegression::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
        m_CustomPlot->replot();
    }
}

void CustomPlotRegression::wheelEvent(QWheelEvent *event){
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

void CustomPlotRegression::updateCustomPlotSize()
{

    if (m_CustomPlot)
    {
        // std::cout << " width() "<< width() << "  height() " << height() << std::endl;
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}

void CustomPlotRegression::onCustomReplot()
{
    //qDebug() << Q_FUNC_INFO;
    update();
}

void CustomPlotRegression::setupQuadraticDemo(double * kernely,
                                              int size_kernely,
                                              double * kernelx,
                                              int size_kernelx  )
{
    QCustomPlot* customPlot=m_CustomPlot;
    // make top right axes clones of bottom left axes:

    // generate some data:
    QVector<double> x1( 0 ), y1( 0 );   // initialize with entries 0..100
    customPlot->addGraph();
    customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
//    customPlot->graph( 0 )->setData( x1, y1 );
    QVector<double> x;
    QVector<double> y;
    std::cout << "****************************************************************+++" <<endl;
    double maxx= DBL_MIN;
    double maxy= DBL_MIN;
    for (int i = 0; i < size_kernelx; i++) {
//        std::cout << kernel[i] << endl;
        x.push_back(kernelx[i]);
        y.push_back(kernely[i]);
        if(kernelx[i] > maxx){
            maxx=kernelx[i];
        }
        if(kernely[i] > maxy){
            maxy=kernely[i];
        }
    }
    m_CustomPlot->graph( 0 )->setData( x, y);
//    std::cout << "ok" << endl;
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));

    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::green ) );
    customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
//    customPlot->graph( 1 )->setData( x1, y1 );
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));

    // give the axes some labels:
    customPlot->xAxis->setLabel( "Generation" );
    customPlot->yAxis->setLabel( "Fitness" );
    // set axes ranges, so we see all data:

    customPlot->xAxis->setRange( 0, maxx );
    customPlot->yAxis->setRange( 0, maxy);

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
}



void CustomPlotRegression::updateGraph0(QVector<double> x,QVector<double> y){

    //     qDebug() << "aggiorno" << endl;
    if (m_CustomPlot)
    {
//        if(x.size() > 20)
//            m_CustomPlot->xAxis->setRange( 0, x.size() );
        m_CustomPlot->graph( 0 )->setData( x, y);
        m_CustomPlot->replot();

    }
}

void CustomPlotRegression::updateGraph1(QVector<double> x,QVector<double> y){

    if (m_CustomPlot)
    {
//        if(x.size() > 20)
//            m_CustomPlot->xAxis->setRange( 0, x.size() );
        m_CustomPlot->graph( 1 )->setData( x, y);
        m_CustomPlot->replot();
    }

}


void CustomPlotRegression::resizeEvent(QResizeEvent *event)
{
    //    qDebug() << "CustomPlotRegression " << endl;
    m_CustomPlot->resize(event->size());
}


