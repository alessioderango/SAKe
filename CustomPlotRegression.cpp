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
    first_time=true;

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
    if(event->button() == Qt::RightButton)
    {
        contextMenuRequest(event->pos());
        //        QRect rec = QApplication::desktop()->screenGeometry();
        //        int height = rec.height();
        //        int width = rec.width();
        //        //TODO controllare geometrie
        //        std::cout << height << std::endl;
        //        std::cout << width << std::endl;
        //        std::cout << event->pos().rx() << std::endl;
        //        std::cout << event->pos().ry() << std::endl;
        //        std::cout << event->pos().x() << std::endl;
        //        std::cout << event->pos().y() << std::endl;
        //std::cout << event->pos() << std::endl;
    }else
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

double gamma_pdf(double alfa, double beta, double x) {
    return boost::math::gamma_p_derivative(alfa, x / beta)/beta;
}

void CustomPlotRegression::addRandomGraph()
{


    //    for (int i = 0; i < number_of_function; ++i) {
    //        if(first_time){
    //            m_CustomPlot->addGraph();
    //        }

    //        QVector<double> y;
    //        for (int i=0; i<number_of_function; i++)
    //        {
    //           y.push_back(gamma_distribution());
    //        }

    //        m_CustomPlot->graph(i+2)->setName(QString("New graph %1").arg(m_CustomPlot->graphCount()-1));
    //        m_CustomPlot->graph(i+2)->setData(x, y);
    //        m_CustomPlot->graph(i+2)->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
    //        QPen graphPen;
    //        graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    //        graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
    //        m_CustomPlot->graph()->setPen(graphPen);
    //        m_CustomPlot->replot();
    //    }



}

void CustomPlotRegression::contextMenuRequest(QPoint pos)
{
    // std::cout << "Right Click" << std::endl;
    QMenu *menu = new QMenu(m_CustomPlot);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
    //    if (m_CustomPlot->selectedGraphs().size() > 0)
    //      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    //    if (m_CustomPlot->graphCount() > 0)
    //      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));

    menu->popup(m_CustomPlot->mapToGlobal(pos));
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

void CustomPlotRegression::drawGammaFunctions(QVector<double> x, QVector<int> functionType, QVector<Parameters> parameter){

    if (m_CustomPlot)
    {

        //        if(x.size() > 20)
        //            m_CustomPlot->xAxis->setRange( 0, x.size() );
        cout << "PLOT " << endl;
        for (int i = 0; i < number_of_function; ++i) {
            if(first_time){
                m_CustomPlot->addGraph();
            }

            QVector<double> y(x.size());

            for (int j = 0; j < x.size(); ++j) {

                if(functionType[i] == 0){
                    y[j]=(parameter[i].getParameters(0)*x[j]+parameter[i].getParameters(1));
                }else{
//                    if(j < parameter[i].getParameters(2))
//                        y[j]=0;
//                    else
//                        y[j]=(gamma_pdf(parameter[i].getParameters(0),parameter[i].getParameters(1),x[j-(parameter[i].getParameters(2)-1)]));
                    y[j]=gamma_pdf(parameter[i].getParameters(0),parameter[i].getParameters(1),x[j]);
                }
            }


            m_CustomPlot->graph(i+2)->setName(QString("New graph %1").arg(m_CustomPlot->graphCount()-1));
            m_CustomPlot->graph(i+2)->setData(x, y);
            m_CustomPlot->graph(i+2)->setLineStyle((QCPGraph::LineStyle)(1));
            QPen graphPen;
            if(functionType[i] == 0){
            graphPen.setColor(QColor(44, 209, 198));
            m_CustomPlot->graph(i+2)->setPen(graphPen);
            }else{
                graphPen.setColor(QColor(160, 44, 209));
                m_CustomPlot->graph(i+2)->setPen(graphPen);
            }
            //m_CustomPlot->replot();
        }
        first_time=false;
    }

}


void CustomPlotRegression::resizeEvent(QResizeEvent *event)
{
    //    qDebug() << "CustomPlotRegression " << endl;
    m_CustomPlot->resize(event->size());
}

std::vector<double> CustomPlotRegression::getX() const
{
    return _x;
}

void CustomPlotRegression::setX(const std::vector<double> &x)
{
    _x = x;
}

int CustomPlotRegression::getNumber_of_function() const
{
    return number_of_function;
}

void CustomPlotRegression::setNumber_of_function(int value)
{
    number_of_function = value;
}



