#include "CustomPlotRegressionPreviewKernel.h"

#include <QDebug>
#include "HandlerCSV.h"

CustomPlotRegressionPreviewKernel::CustomPlotRegressionPreviewKernel(QQuickItem* parent ) : QQuickPaintedItem( parent )
  , m_CustomPlot( nullptr )
{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );

    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotRegressionPreviewKernel::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotRegressionPreviewKernel::updateCustomPlotSize );
}

CustomPlotRegressionPreviewKernel::~CustomPlotRegressionPreviewKernel()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotRegressionPreviewKernel::initCustomPlotRegressionPreviewKernel()
{
    m_CustomPlot = new QCustomPlot();
    //m_CustomPlot->setMinimumHeight(200);
    updateCustomPlotSize();

    setupQuadraticDemo( m_CustomPlot );

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotRegressionPreviewKernel::onCustomReplot );

    m_CustomPlot->replot();
}


void CustomPlotRegressionPreviewKernel::paint( QPainter* painter )
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

void CustomPlotRegressionPreviewKernel::mousePressEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotRegressionPreviewKernel::mouseReleaseEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotRegressionPreviewKernel::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotRegressionPreviewKernel::mouseDoubleClickEvent( QMouseEvent* event )
{
    //qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotRegressionPreviewKernel::graphClicked( QCPAbstractPlottable* plottable )
{
    //qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotRegressionPreviewKernel::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
        m_CustomPlot->replot();
    }
}

void CustomPlotRegressionPreviewKernel::wheelEvent(QWheelEvent *event){
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

void CustomPlotRegressionPreviewKernel::updateCustomPlotSize()
{

    if (m_CustomPlot)
    {
        // std::cout << " width() "<< width() << "  height() " << height() << std::endl;
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}

void CustomPlotRegressionPreviewKernel::onCustomReplot()
{
    //qDebug() << Q_FUNC_INFO;
    update();
}

void CustomPlotRegressionPreviewKernel::setupQuadraticDemo(QCustomPlot* m_CustomPlot)
{
    QCustomPlot* customPlot=m_CustomPlot;

    // make top right axes clones of bottom left axes:
    // generate some data:
    QVector<double> x1( 0 ), y1( 0 );   // initialize with entries 0..100
    customPlot->addGraph();
    customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 0 )->setData( x1, y1 );
customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::green ) );
    customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 1 )->setData( x1, y1 );
customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    // give the axes some labels:
//    customPlot->xAxis->setLabel( "Generation" );
//    customPlot->yAxis->setLabel( "Fitness" );
//    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange( 0, 180 );
    customPlot->yAxis->setRange(  -0.01,0.25 );

    myBars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(myBars);
    // now we can modify properties of myBars:
    myBars->setName("Bars Series 1");



    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
}

void CustomPlotRegressionPreviewKernel::updateGraph(double* Fi,int tb) const{
    if (m_CustomPlot)
    {
        //     qDebug() << "aggiorno" << endl;
        QVector<double> keyData;
        QVector<double> valueData;
        for (int i = 0; i < tb; i++) {
            keyData.push_back(i+1);
            valueData.push_back(Fi[i]);
        }
        myBars->setData(keyData, valueData);
        //m_CustomPlot->rescaleAxes();
        m_CustomPlot->replot();
    }
}


void CustomPlotRegressionPreviewKernel::updateGraph0(QVector<double> x,QVector<double> y){

    //     qDebug() << "aggiorno" << endl;
    if (m_CustomPlot)
    {
//        if(x.size() > 20)
//            m_CustomPlot->xAxis->setRange( 0, x.size() );
        m_CustomPlot->graph( 0 )->setData( x, y);
        m_CustomPlot->replot();

    }
}

void CustomPlotRegressionPreviewKernel::updateGraph1(QVector<double> x,QVector<double> y){

    if (m_CustomPlot)
    {
//        if(x.size() > 20)
//            m_CustomPlot->xAxis->setRange( 0, x.size() );
        m_CustomPlot->graph( 1 )->setData( x, y);
        m_CustomPlot->replot();
    }

}


void CustomPlotRegressionPreviewKernel::resizeEvent(QResizeEvent *event)
{
    //    qDebug() << "CustomPlotRegressionPreviewKernel " << endl;
    m_CustomPlot->resize(event->size());
}

void getSubdividePointsFromKernel( double *kernel,int size_kernel,int n,QVector<double> &x, QVector<double> &y){

    double sumx=0;
    double sumy=0;
    int end = ((size_kernel%n)==0) ? size_kernel : (size_kernel-n);
    for (int i = 0; i < end; i+=n) {
        sumx=0;
        sumy=0;
        for (int j = 0; j < n; j++) {
            sumx+=j+(i+1);
            sumy+=kernel[j+i];
        }
        x.push_back(sumx/n);
        y.push_back(sumy/n);
    }
    if(size_kernel%n !=0){
        sumx=0;
        sumy=0;
        int count=0;
        for (int i = (size_kernel-(n-1)); i < size_kernel; i++) {
            sumx+=(i+1);
            sumy+=kernel[i];
             count++;
        }
        x.push_back(sumx/count);
        y.push_back(sumy/count);
    }
}

void getSubdividePointsFromControlPoints(std::vector< double> x,std::vector< double> y,int n,QVector<double> &xOutput, QVector<double> &yOutput){
    double sumx=0;
    double sumy=0;
    int end = ((y.size()%n)==0) ? y.size() : (y.size()-n);
    for (int i = 0; i < end; i+=n) {
        sumx=0;
        sumy=0;
        for (int j = 0; j < n; j++) {
            sumx+=x[j+i];
            sumy+=y[j+i];
        }
        xOutput.push_back(sumx/n);
        yOutput.push_back(sumy/n);
    }

    if(y.size()%n !=0){
        sumx=0;
        sumy=0;
        int count=0;
        for (int i = (y.size()-(n-1)); i < y.size(); i++) {
            sumx+=x[i];
            sumy+=y[i];
            count++;
        }
        xOutput.push_back(sumx/count);
        yOutput.push_back(sumy/count);
    }


}
void CustomPlotRegressionPreviewKernel::customPlotRegressionSubdivideFromControlPoints(const QVariant& n)
{
    m_CustomPlot->xAxis->setRange( 0, size_kernel );
    ControlPoints * controlPoints = new ControlPoints();
    controlPoints->calculateControlPoints(kernel,size_kernel);
    std::vector< double> x = controlPoints->getX();
    std::vector< double> y = controlPoints->getY();
    QVector<double> xOutput;
    QVector<double> yOutput;
    getSubdividePointsFromControlPoints(x,y,n.toInt(),xOutput,yOutput);
    updateGraph0(xOutput,yOutput);
}
void CustomPlotRegressionPreviewKernel::customPlotRegressionSubdivideFromKernel(const QVariant& n)
{
    //    customPlot->yAxis->setRange( 0, maxy);
    m_CustomPlot->xAxis->setRange( 0, size_kernel );

    QVector<double> xOutput;
    QVector<double> yOutput;
    getSubdividePointsFromKernel(kernel,size_kernel,n.toInt(),xOutput,yOutput);
    updateGraph0(xOutput,yOutput);
}

void CustomPlotRegressionPreviewKernel::initCustomPlotRegressionPreviewKernel(const QVariant &filenamePar)
{
    filename = filenamePar;
    HandlerCSV::loadCSVKernel(filename.toString(),kernel,size_kernel,Delta_cr);
    m_CustomPlot->xAxis->setRange( 0, size_kernel );

    updateGraph(kernel,size_kernel);

    ControlPoints * controlPoints = new ControlPoints();
    controlPoints->calculateControlPoints(kernel,size_kernel);
    std::vector< double> x = controlPoints->getX();
    std::vector< double> y = controlPoints->getY();

    updateGraph1(QVector<double>::fromStdVector (x),QVector<double>::fromStdVector (y));


    delete controlPoints;

    m_CustomPlot->replot();
}

void CustomPlotRegressionPreviewKernel::initCustomPlotKernelComtrolPoints()
{
    ControlPoints * controlPoints = new ControlPoints();
    controlPoints->calculateControlPoints(kernel,size_kernel);
    std::vector< double> x = controlPoints->getX();
    std::vector< double> y = controlPoints->getY();

    updateGraph1(QVector<double>::fromStdVector (x),QVector<double>::fromStdVector (y));
    delete controlPoints;

    m_CustomPlot->replot();
}


