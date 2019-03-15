#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "validation.h"
#include "Regression.h"
#include "Regression/regressioncontroller.h"

#include <algorithm>

std::vector<QThread *> MainWindow::threads;


QTabWidget *MainWindow::getTabbyPos(int pos)
{
    return (QTabWidget*)ui->tabWidget_2->widget(pos);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(1,80);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    xmlmanager = new XMLManager();
    xmlmanager->setTreeview(ui->treeWidget);
    xmlmanager->ReadCalibrationProjectXML();
    emit expandTreeViewSignals();
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem * , int )), this, SLOT(myClick(QTreeWidgetItem * , int )));
    connect(ui->treeWidget,&QTreeWidget::customContextMenuRequested,this,&MainWindow::prepareMenu);
    ui->tabWidget_2->setTabsClosable(true);
    ui->tabWidget_2->removeTab(0);
    ui->tabWidget_2->removeTab(0);
    //ui->tabWidget_2->setMovable(true);
    signalMapper = new QSignalMapper(this);
    signalMapperCopy = new QSignalMapper(this);
    connect (this, SIGNAL(expandTreeViewSignals()), this, SLOT(expandTreeViewSlot())) ;


}

// painting function preview kernel regression ----------------------------------------------------------------

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


// painting function preview kernel regression ----------------------------------------------------------------



void MainWindow::makeFitnessPlot(QCustomPlot * customPlot){

    // generate some data:
    QVector<double> x1( 0 ), y1( 0 );   // initialize with entries 0..100
    customPlot->addGraph();
    customPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    //customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 0 )->setData( x1, y1 );
    customPlot->graph( 0 )->setName("Maximum Fitness");

    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::green ) );
    //customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 1 )->setData( x1, y1 );
    customPlot->graph( 1 )->setName("Average Fitness");

    // give the axes some labels:
    customPlot->xAxis->setLabel( "generation" );
    customPlot->yAxis->setLabel( "fitness" );
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange( 0, 20 );
    customPlot->yAxis->setRange( 0, 1.05 );

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestFitness(QPoint)));


    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, "Fitness history"));
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));

}

void MainWindow::makeAUCROCPlot(QCustomPlot *customPlot)
{
    QVector<double> x1( 0 ), y1( 0 );
    double incr = 0.2;
    for (int i = 0; i <= 5; ++i) {
         x1.push_back(incr*i);
         y1.push_back(incr*i);
    }

    customPlot->addGraph();
    QPen pen;
    pen.setColor(QColor(qSin(1*1+1.2)*80+80, qSin(1*0.3+0)*80+80, qSin(1*0.3+1.5)*80+80));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName("diagonal");
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    customPlot->graph()->setData(x1, y1);
    customPlot->graph()->rescaleAxes(true);

    customPlot->addGraph();
    pen.setColor(QColor(qSin(4*1+1.2)*80+80, qSin(4*0.3+0)*80+80, qSin(4*0.3+1.5)*80+80));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName("ROC");
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    customPlot->graph()->setData(x1, y1);
    customPlot->graph()->rescaleAxes(true);


    customPlot->xAxis->setRange( 0, 1 );
    customPlot->yAxis->setRange( 0, 1 );

    customPlot->xAxis->setLabel( "FPR or (1-specificity)" );
    customPlot->yAxis->setLabel( "TPR or sensitivity" );

    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestAUCROC(QPoint)));


}


void MainWindow::makeDETPlot(QCustomPlot *customPlot)
{
    QVector<double> x1( 0 ), y1( 0 );
    double incr = 0.2;
    for (int i = 0; i <= 5; ++i) {
         x1.push_back(incr*i);
         y1.push_back(incr*i);
    }

    customPlot->addGraph();
    QPen pen;
    pen.setColor(QColor(qSin(1*1+1.2)*80+80, qSin(1*0.3+0)*80+80, qSin(1*0.3+1.5)*80+80));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName("DET");
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    customPlot->graph()->setData(x1, y1);
    customPlot->graph()->rescaleAxes(true);

    customPlot->xAxis->setRange( 0, 1 );
    customPlot->yAxis->setRange( 0, 1 );

    customPlot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);


    QVector<double> TickValues;
    QVector<QString> TickLabels;
    // you can safely change the values according to the output
    TickValues << 0 <<0.1  <<0.2  <<0.3  <<0.4  <<0.5  <<0.6  <<0.7 <<0.8  <<0.9 <<1  <<2  <<3  <<4  <<5  <<6  <<7 <<8  <<9<< 10 << 20 << 30 << 40 << 50 << 60 << 70 << 80<< 90 << 100;
    TickLabels << "0" <<"0.1%"  <<"0.2%"  <<"0.3%"  <<"0.4%"  <<"0.5%"  <<"0.6%"  <<"0.7%" <<"0.8%"  <<"0.9%" <<"1%"  <<"2%"  <<"3%"  <<"4%"  <<"5%"  <<"6%"  <<"7%" <<"8%"  <<"9%"<< "10%" << "20%"<< "30%" << "40%"<< "50%" << "60%"<< "70%" << "80%"<< "90%" << "100%";
    // disable default ticks and their labels
    customPlot->yAxis->setAutoTicks(false);
    customPlot->yAxis->setAutoTickLabels(false);
    // add your custom values and labels
    customPlot->yAxis->setTickVector(TickValues);
    customPlot->yAxis->setTickVectorLabels(TickLabels);

    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    // add your custom values and labels
    customPlot->xAxis->setTickVector(TickValues);
    customPlot->xAxis->setTickVectorLabels(TickLabels);

    customPlot->xAxis->setLabel( "False positive rate or false alarms rate" );
    customPlot->yAxis->setLabel( "False negative rate or missed  detection rate" );

    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);

    //connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestAUCROC(QPoint)));


}

void MainWindow::makeMobilityFunctionPlot(QCustomPlot * customPlot,Rain * rain, int rain_size, Activation *activation, int activation_size){


    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));

    customPlot->addGraph();
    //
    customPlot->graph( 0 )->setPen( QPen( Qt::red,0.5 ) );
    //customPlot->graph( 0 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->yAxis->setRange( 0,20 );

    customPlot->addGraph();
    customPlot->graph(1)->setPen( QPen( Qt::gray ,0.5 ) );

    QVector<double> timetmp(rain_size),ytime(rain_size);
    for (int i=0; i<rain_size; i++){
        timetmp[i]=(ptime_from_tm(rain[i].getTime())-ptime(date(1970, Jan, 1))).total_seconds();
        ytime[i]=0;
    }

    customPlot->graph(1)->setData(timetmp, ytime);

    customPlot->addGraph();

    customPlot->graph(2)->setPen( QPen( Qt::blue ,0.5) );

    customPlot->graph(2)->setData(timetmp, ytime);

    customPlot->addGraph();
    customPlot->graph(3)->setPen( QPen( Qt::blue,0.5  ) );
    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 7));

    //    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    //    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    //    dateTimeTicker->setDateTimeFormat("dd-MMMM-yyyy");
    //    customPlot->xAxis->setTicker(dateTimeTicker);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("dd\nMMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set a fixed tick-step to one tick per month:
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis->setTickStep(2628000); // one month in seconds

    customPlot->xAxis->setLabel("Date");
    customPlot->yAxis->setLabel("z");


    ptime rain0 = ptime_from_tm(rain[0].getTime());
    ptime rainLast = ptime_from_tm(rain[rain_size-1].getTime());
    boost::posix_time::time_duration diff1 =(rain0-ptime(date(1970, Jan, 1)));
    boost::posix_time::time_duration diff2 = (rainLast-ptime(date(1970, Jan, 1)));
    //      cout << diff1.total_seconds()<< " "<<diff2.total_seconds() << endl;

    customPlot->xAxis->setRange(diff1.total_seconds(), diff2.total_seconds());
    customPlot->yAxis->setRange( 0, 20 );


    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    //connect( customPlot, SIGNAL( plottableClick( QCPAbstractPlottable*, QMouseEvent* ) ), this, SLOT( graphClicked( QCPAbstractPlottable* ) ) );
    //connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    //connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    bool first = true;
    int graphnum=4;
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
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestMobilityFunction(QPoint)));

    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, "Mobility function related to Bkci"));
}

void MainWindow:: makeKernelPlot(QCustomPlot *customPlot,MainWindow * w)
{
    QCPBars* myBars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(myBars);
    // now we can modify properties of myBars:
    myBars->setName("Bars Series 1");
    customPlot->xAxis->setLabel("tb");
    customPlot->yAxis->setLabel("h");
    customPlot->xAxis->setRange( 1,180 );
    customPlot->yAxis->setRange( -0.01,0.25 );
    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);

    //add graph for preview kernel control points
    //customPlot->addGraph();

    //add graph for preview kernel
    customPlot->addGraph();
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    customPlot->graph(0)->setPen( QPen( Qt::green ) );
    customPlot->addGraph();


    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), w, SLOT(contextMenuRequestKernel(QPoint)));

}

void MainWindow::updateFitnessPlot(int indexTab, QVector<double> x, QVector<double> y, QVector<double> x1, QVector<double> y1, int numberofGenerations, bool b)
{
    QCustomPlot *m_CustomPlot = getFitnessPlot(indexTab);
    if (m_CustomPlot)
    {
        m_CustomPlot->xAxis->setRange( 0, x.size() );
        m_CustomPlot->graph( 0 )->setData( x, y);
        m_CustomPlot->replot();

        m_CustomPlot->xAxis->setRange( 0, x1.size() );
        m_CustomPlot->graph( 1 )->setData( x1, y1);
        m_CustomPlot->replot();

        if(numberofGenerations != 0 && b){
            m_CustomPlot->addGraph();
            m_CustomPlot->graph(2)->setBrush(QBrush(QColor(169,169,169, 20)));
            QVector<double > tmpx;
                    for (int i = 0; i <= numberofGenerations; ++i)
                            tmpx.push_back(x[i]);
            QVector<double > tmpy;
                          for (int i = 0; i <= numberofGenerations; ++i)
                                    tmpy.push_back(y[i]);
            m_CustomPlot->graph(2)->setData(tmpx,tmpy);


            m_CustomPlot->addGraph();


            m_CustomPlot->graph(3)->setBrush(QBrush(QColor(169,169,169, 20)));
            QVector<double > tmpx1;
                    for (int i = 0; i <= numberofGenerations; ++i)
                            tmpx1.push_back(x1[i]);
            QVector<double > tmpy1;
                          for (int i = 0; i <= numberofGenerations; ++i)
                                    tmpy1.push_back(y1[i]);
            m_CustomPlot->graph(3)->setData( tmpx1,tmpy1);

        }
    }

}

void MainWindow::updateKernelPlot(int indexTab, QVector<double> Fi, int tb)
{
    QCustomPlot *m_CustomPlot = getKernelPlot(indexTab);
    if (m_CustomPlot)
    {


        QVector<double> keyData;
        for (int i = 0; i < tb; i++) {
            keyData.push_back(i);
        }
        ((QCPBars*)m_CustomPlot->plottable(0))->setData(keyData, Fi);
        //myBars->setData(keyData, Fi);
        // m_CustomPlot->xAxis->setRange( 0,tb );
        //m_CustomPlot->rescaleAxes();
        m_CustomPlot->replot();


    }

}


void MainWindow::updateKernelPlotRegression(QCustomPlot *m_CustomPlot, QVector<double> xKernel,QVector<double> yKernel,QVector<double> xControlpoints,QVector<double> yControlpoints )
{
    if (m_CustomPlot)
    {
        m_CustomPlot->graph(0)->setData(xControlpoints, yControlpoints);
        ((QCPBars*)m_CustomPlot->plottable(0))->setData(xKernel, yKernel);
        m_CustomPlot->replot();
    }

}

void MainWindow::updateKernelPlotRegressionWithControlPoints(QCustomPlot *m_CustomPlot,QVector<double> xControlpoints,QVector<double> yControlpoints )
{
    if (m_CustomPlot)
    {
        m_CustomPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
        m_CustomPlot->graph(1)->setPen( QPen( Qt::red ) );

        m_CustomPlot->graph(1)->setData(xControlpoints, yControlpoints);
        m_CustomPlot->replot();
    }

}

void MainWindow::updateROCPlot(int indexTab, QVector<double> FPR, QVector<double> TPR, double AUCROC)
{
    mutex.lock();
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    //PLOT ROC e AUC
    QCustomPlot *m_CustomPlot = getAUCROCPlot(indexTab);
    if (m_CustomPlot)
    {
        (m_CustomPlot->graph(1))->setData(FPR, TPR);

        m_CustomPlot->replot();
    }

    m_CustomPlot = (QCustomPlot*)tabs->findChild<QCustomPlot*>("DET");
    if (m_CustomPlot)
    {

        for (int i = 0; i < FPR.size(); ++i) {
            QVector<double> FNRPerc(2,0);
            QVector<double> FPRPerc(2,0);
            FPRPerc[0]=0;
            FNRPerc[1] = (double)(((double)1)-TPR[i])*100;

            FPRPerc[0] = FPR[i]*100;
            FPRPerc[1] = 0;
            m_CustomPlot->addGraph();
            (m_CustomPlot->graph(i))->setData(FPRPerc,FNRPerc);
            cout << FPRPerc[0] << "   " <<FNRPerc[0] << endl;
            cout << FPRPerc[1] << "   " <<FNRPerc[1] << endl;

        }


        m_CustomPlot->replot();
    }

    QLabel* text = (QLabel*)tabs->findChild<QLabel*>("AUCValue");
    text->setText(QString("%1").arg(AUCROC));
    mutex.unlock();
}


void MainWindow::updateTextsRegression(int indexTab, QString s, QString fitness, QString cuavfitness, int barValue, int firstOccurence, QString abmaxfitness, QString avmaxfitness)
{
    mutex.lock();
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QLabel* text = (QLabel*)tabs->findChild<QLabel*>("GenerationText");
    text->setText(s);

    QLabel* curMaxFit = (QLabel*)tabs->findChild<QLabel*>("curMaxFitNum");
    curMaxFit->setText(fitness);
    QLabel* curAvFit = (QLabel*)tabs->findChild<QLabel*>("curAveFitNum");
    curAvFit->setText(cuavfitness);

    QLabel* bestfndatItera = (QLabel*)tabs->findChild<QLabel*>("firstOccurenceText");
    QString fo = QString("Iteration of first occurence of AMF : %1").arg(firstOccurence);
    bestfndatItera->setText(fo);
    QProgressBar* bar = (QProgressBar*)tabs->findChild<QProgressBar*>("bar");
    bar->setValue(barValue);

    QLabel* AbsMaxFitNum = (QLabel*)tabs->findChild<QLabel*>("AbsMaxFitNum");
    AbsMaxFitNum->setText(abmaxfitness);
    QLabel* AbsAveFitNum = (QLabel*)tabs->findChild<QLabel*>("AbsAveFitNum");
    AbsAveFitNum->setText(avmaxfitness);

    mutex.unlock();
}

void MainWindow::updateRegression(int indexTab,
                       QVector<double> x,
                       QVector<double> y,
                       QVector<double> xReal,
                       QVector<double> yReal,
                       int numberofFunction,
                       std::vector< std::vector<double> > matrixY,
                       int steps,
                       std::vector<QCPItemText*> widgetArray,
                       std::vector<QCPItemLine*> arrowArray,
                       std::vector< std::vector<double> > matrixParameters){

    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QCustomPlot* plot = (QCustomPlot*)tabs->findChild<QCustomPlot*>("FuncPlot");
    QTableWidget * tableResult= (QTableWidget*)tabs->findChild<QTableWidget*>("tableResult");

   //
    plot->graph(1)->setData(xReal, yReal);


   // int shift = x.size()/numberofFunction;

    if(steps==5)
    {
      //plot->graph(0)->setVisible(false);
      //plot->graph(1)->rescaleAxes();
      plot->rescaleAxes(true);
      //plot->graph(0)->setVisible(true);
      tableResult->setRowCount(numberofFunction);


    }
    plot->graph(0)->setData(x, y);
    for (int i = 0; i < numberofFunction; ++i) {
       QVector<double> yFunction = QVector<double>::fromStdVector(matrixY[i]);
        plot->graph(i+2)->setData(x, yFunction);

        //double *max = max_element(yFunction.begin(), yFunction.end());
        int xDistance = distance(yFunction.begin(), max_element(yFunction.begin(), yFunction.end()));
        widgetArray[i]->position->setCoords(x[xDistance],yFunction[xDistance]+(0.02));
        QString a = QString("w, a, b, t\n %1, %2, %3, %4").arg(matrixParameters[i][0]).arg(matrixParameters[i][1]).arg(matrixParameters[i][2]).arg(matrixParameters[i][3]);
        widgetArray[i]->setText(a);
        arrowArray[i]->end->setCoords(x[xDistance],yFunction[xDistance]);
        QLabel* nrow = new QLabel();
        QString s= QString("%1").arg(i+1);
        nrow->setText(s);
        tableResult->setCellWidget(i, 0, nrow);

        s= QString("%1").arg(matrixParameters[i][0]);

        nrow = new QLabel();
        nrow->setText(s);
        tableResult->setCellWidget(i, 1, nrow);
        s= QString("%1").arg(matrixParameters[i][1]);
        nrow = new QLabel();
        nrow->setText(s);
        tableResult->setCellWidget(i, 2, nrow);

        s= QString("%1").arg(matrixParameters[i][2]);
        nrow = new QLabel();
        nrow->setText(s);
        tableResult->setCellWidget(i, 3, nrow);

        s= QString("%1").arg(matrixParameters[i][3]);
        nrow = new QLabel();
        nrow->setText(s);
        tableResult->setCellWidget(i, 4, nrow);
    }
    plot->replot();








}

void MainWindow::updateTexts(int indexTab,
                             QString s,
                             QString fitness,
                             QString cuavfitness,
                             QString tb,
                             QString Zjmin,
                             QString Zcr,
                             QString safetyMargin,
                             QString momentum,
                             int barValue, int firstOccurence,
                             QString abmaxfitness,
                             QString avmaxfitness)
{
    mutex.lock();
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QLabel* text = (QLabel*)tabs->findChild<QLabel*>("GenerationText");
    text->setText(s);


    //    QLabel* absMaxFit = (QLabel*)tabs->findChild<QLabel*>("GenerationText");
    //    absMaxFit->setText("0");
    //    QLabel* absAvFit = (QLabel*)tabs->findChild<QLabel*>("GenerationText");
    //    absAvFit->setText("0");
    QLabel* curMaxFit = (QLabel*)tabs->findChild<QLabel*>("curMaxFitNum");
    curMaxFit->setText(fitness);
    QLabel* curAvFit = (QLabel*)tabs->findChild<QLabel*>("curAveFitNum");
    curAvFit->setText(cuavfitness);
    QLabel* tbL = (QLabel*)tabs->findChild<QLabel*>("tbNum");
    tbL->setText(tb);

    QLabel* ZjminL = (QLabel*)tabs->findChild<QLabel*>("ZjminNum");
    ZjminL->setText(Zjmin);
    QLabel* ZcrL = (QLabel*)tabs->findChild<QLabel*>("ZcrNum");
    ZcrL->setText(Zcr);

    QLabel* safetyMArginL = (QLabel*)tabs->findChild<QLabel*>("dCriticoNum");
    safetyMArginL->setText(safetyMargin);

    QLabel* momentumL = (QLabel*)tabs->findChild<QLabel*>("momPrimoNum");
    momentumL->setText(momentum);

    QLabel* bestfndatItera = (QLabel*)tabs->findChild<QLabel*>("firstOccurenceText");
    QString fo = QString("Iteration of first occurence of AMF : %1").arg(firstOccurence);
    bestfndatItera->setText(fo);
    QProgressBar* bar = (QProgressBar*)tabs->findChild<QProgressBar*>("bar");
    bar->setValue(barValue);

    QLabel* AbsMaxFitNum = (QLabel*)tabs->findChild<QLabel*>("AbsMaxFitNum");
    AbsMaxFitNum->setText(abmaxfitness);
    QLabel* AbsAveFitNum = (QLabel*)tabs->findChild<QLabel*>("AbsAveFitNum");
    AbsAveFitNum->setText(avmaxfitness);
//    AbsMaxFitNum
//            AbsAveFitNum


    mutex.unlock();

}

void MainWindow::updateTextsValidation(int indexTab, QString fitness, QString tb, QString safetyMargin, QString momentum)
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);

    QLabel* curMaxFit = (QLabel*)tabs->findChild<QLabel*>("curMaxFitNum");
    curMaxFit->setText(fitness);

    QLabel* tbL = (QLabel*)tabs->findChild<QLabel*>("tbNum");
    tbL->setText(tb);
    QLabel* safetyMArginL = (QLabel*)tabs->findChild<QLabel*>("dCriticoNum");
    safetyMArginL->setText(safetyMargin);

    QLabel* momentumL = (QLabel*)tabs->findChild<QLabel*>("momPrimoNum");
    momentumL->setText(momentum);

}

void MainWindow::updateTextsValidationAllInOne(int indexTab,QString name, QString fitness, QString tb, QString safetyMargin, QString momentum, QString Zjmin, QString Zcr)
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);

    QLabel* curMaxFit = (QLabel*)tabs->findChild<QLabel*>("curMaxFitNum"+name);
    curMaxFit->setText(fitness);

    QLabel* tbL = (QLabel*)tabs->findChild<QLabel*>("tbNum"+name);
    tbL->setText(tb);
    QLabel* safetyMArginL = (QLabel*)tabs->findChild<QLabel*>("dCriticoNum"+name);
    safetyMArginL->setText(safetyMargin);

    QLabel* momentumL = (QLabel*)tabs->findChild<QLabel*>("momPrimoNum"+name);
    momentumL->setText(momentum);

    QLabel* ZjminL = (QLabel*)tabs->findChild<QLabel*>("ZjminNum");
    ZjminL->setText(Zjmin);

    QLabel* ZcrL = (QLabel*)tabs->findChild<QLabel*>("ZcrNum");
    ZcrL->setText(Zcr);

}
void MainWindow::updateTextsValidationAllInOneFitness(int indexTab,QString name, QString fitness)
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);

    QLabel* curMaxFit = (QLabel*)tabs->findChild<QLabel*>("curMaxFitNum"+name);
    curMaxFit->setText(fitness);

}

void MainWindow::updateAbsMaxFit(int indexTab, QString s)
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QLabel* absMaxFit = (QLabel*)tabs->findChild<QLabel*>("AbsMaxFitNum");
    absMaxFit->setText(s);

}

void MainWindow::updateAbsAvFit(int indexTab, QString s)
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QLabel* absAvFit = (QLabel*)tabs->findChild<QLabel*>("AbsAveFitNum");
    absAvFit->setText(s);
}

void MainWindow::getMoreInfoROC()
{

}

void MainWindow::updateMobPlot(int indexTab, Rain * rain, int rain_size, Activation *activation, int activation_size, std::vector<double> Y, double YmMinVal, tm YmMinTime, double YmMinVal2, tm  YmMinTime2, std::vector<Ym> bests, std::vector<QCPItemText*> widgetArray,
                               std::vector<QCPItemLine*> arrowArray)
{
    QCustomPlot *m_CustomPlot = getPlotMobility(indexTab,"");
    if (m_CustomPlot)
    {
        m_CustomPlot->axisRect()->setRangeDrag(0);
        m_CustomPlot->axisRect()->setRangeZoom(0);

        std::sort(bests.begin(), bests.end(), [](Ym a, Ym b) { return a.getValue() > b.getValue(); });


        for(unsigned int i = 0; i < bests.size();i++){

            ptime bestTmp = ptime_from_tm(bests[i].getTime());
            boost::posix_time::time_duration diff =(bestTmp-ptime(date(1970, Jan, 1)));
            widgetArray[i]->position->setCoords(diff.total_seconds(), bests[i].getValue()+8);

            //DateTime time = DateTime(t.tm_year+1900, t.tm_mon+1, t.tm_day, t.tm_hour, t.tm_min, t.tm_sec);
            int year = bests[i].getTime().tm_year +1900;
            int mon = bests[i].getTime().tm_mon +1;
            int day = bests[i].getTime().tm_mday ;
            //std::cout << "year " << year << " mon " << mon << " day " << day << std::endl;
            ////            string year = std::to_string(1900);
            ////            string mon = bests[i].getTime().tm_mon+std::to_string(1);
            ////            string day = bests[i].getTime().day;

            QString a = QString("%1 %2 %3 - %4").arg(year).arg(mon).arg(day).arg(bests[i].getI());
            widgetArray[i]->setText(a);
            arrowArray[i]->end->setCoords(diff.total_seconds(), bests[i].getValue());
        }


        m_CustomPlot->graph( 0 )->setPen( QPen( Qt::red ) );
        //    qDebug() << "aggiorno" << endl;
        //m_CustomPlot->graph(0)->data()->clear();
        double max =-1;
        QVector<double> time(rain_size), value(rain_size);
        for (int i=0; i<rain_size; i++)
        {
            ptime raintime = ptime_from_tm(rain[i].getTime());
            boost::posix_time::time_duration diff =(raintime-ptime(date(1970, Jan, 1)));
            time[i] = diff.total_seconds();
            value[i]=Y[i];
            if(value[i] > max)
               max=value[i];
        }

        m_CustomPlot->graph(0)->setData(time, value);

        QVector<double> ytime(rain_size),ytime2(rain_size);
        for (int i=0; i<rain_size; i++){
            //timetmp[i]=(ptime_from_tm(rain[i].getTime())-ptime(date(1970, Jan, 1))).total_seconds();
            ytime[i]=YmMinVal;//YmMin->getValue();
            ytime2[i]=YmMinVal2;//YmMin2->getValue();
        }
        m_CustomPlot->graph(1)->setData(time, ytime);
        m_CustomPlot->graph(2)->setData(time, ytime2);

        QVector<double> yPoint(2),xPoint(2);

        yPoint[0]=YmMinVal;//YmMin->getValue();
        yPoint[1]=YmMinVal2;//YmMin2->getValue();
        xPoint[0]=(ptime_from_tm(YmMinTime)-ptime(date(1970, Jan, 1))).total_seconds();
        xPoint[1]=(ptime_from_tm(YmMinTime2)-ptime(date(1970, Jan, 1))).total_seconds();
        m_CustomPlot->graph(3)->setData(xPoint, yPoint);
        m_CustomPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
        m_CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
        //m_CustomPlot->setOpenGl(true);
        int graphnum=4;
        QVector<double> x(max), y(max);
        for (int j=0; j<activation_size; j++)
        {
            tm a1=activation[j].getStart();
            //a1.tm_mday-=1;
            //cout << a1.tm_mday<< " "<<a1.tm_mon<< " "<<a1.tm_year << endl;
            tm a2=activation[j].getEnd();
            // cout << a1.tm_mday<< " "<<a1.tm_mon<< " "<<a1.tm_year<< endl;
            //a2.tm_mday+=2;
            for (int k=0; k<2; k++)
            {
                //m_CustomPlot->addGraph();
                for (int i=0; i<(int)max; i++)
                {

                    if(k%2==0){

                        m_CustomPlot->graph( graphnum )->setPen( QPen( Qt::green) );

                        ptime tmp1 = ptime_from_tm(a1);
                        //ptime t11 = local_adj::utc_to_local(tmp1);

                        ptime utcepoch = ptime(date(1970, Jan, 1));
                        //ptime utcepoch1 = local_adj::utc_to_local(utcepoch);
                        //std::cout << (raindate-ptime(date(1970, Jan, 1))).total_milliseconds() << "\n";
                        boost::posix_time::time_duration diff =(tmp1-utcepoch);
                        //diff.total_milliseconds();
                        x[i] = diff.total_seconds();
                    }else{

                        m_CustomPlot->graph( graphnum )->setPen( QPen( Qt::blue) );
                        ptime tmp2 = ptime_from_tm(a2);
                        x[i] =(tmp2-ptime(date(1970, Jan, 1))).total_seconds();
                    }
                    y[i] = i;

                    //cout << x[i] << " "<< y[i]  << endl;
                }

                m_CustomPlot->graph(graphnum)->setData(x, y);
                // customPlot->graph(graphnum)->rescaleAxes(true);
                graphnum++;
            }


        }
        m_CustomPlot->replot();
    }
}

void MainWindow::updateMobPlotAllInOne(int indexTab, QString name, Rain * rain, int rain_size, Activation *activation, int activation_size, std::vector<double> Y, double YmMinVal, tm YmMinTime, double YmMinVal2, tm  YmMinTime2, std::vector<Ym> bests, std::vector<QCPItemText*> widgetArray,
                               std::vector<QCPItemLine*> arrowArray)
{
    QCustomPlot *m_CustomPlot = getPlotMobility(indexTab,name);
    if (m_CustomPlot)
    {
        m_CustomPlot->axisRect()->setRangeDrag(0);
        m_CustomPlot->axisRect()->setRangeZoom(0);

        std::sort(bests.begin(), bests.end(), [](Ym a, Ym b) { return a.getValue() > b.getValue(); });


        for(unsigned int i = 0; i < bests.size();i++){

            ptime bestTmp = ptime_from_tm(bests[i].getTime());
            boost::posix_time::time_duration diff =(bestTmp-ptime(date(1970, Jan, 1)));
            widgetArray[i]->position->setCoords(diff.total_seconds(), bests[i].getValue()+8);

            //DateTime time = DateTime(t.tm_year+1900, t.tm_mon+1, t.tm_day, t.tm_hour, t.tm_min, t.tm_sec);
            int year = bests[i].getTime().tm_year +1900;
            int mon = bests[i].getTime().tm_mon +1;
            int day = bests[i].getTime().tm_mday ;
            //std::cout << "year " << year << " mon " << mon << " day " << day << std::endl;
            ////            string year = std::to_string(1900);
            ////            string mon = bests[i].getTime().tm_mon+std::to_string(1);
            ////            string day = bests[i].getTime().day;

            QString a = QString("%1 %2 %3 - %4").arg(year).arg(mon).arg(day).arg(bests[i].getI());
            widgetArray[i]->setText(a);
            arrowArray[i]->end->setCoords(diff.total_seconds(), bests[i].getValue());
        }


        m_CustomPlot->graph( 0 )->setPen( QPen( Qt::red ) );
        //    qDebug() << "aggiorno" << endl;
        //m_CustomPlot->graph(0)->data()->clear();
        double max =-1;
        QVector<double> time(rain_size), value(rain_size);
        for (int i=0; i<rain_size; i++)
        {
            ptime raintime = ptime_from_tm(rain[i].getTime());
            boost::posix_time::time_duration diff =(raintime-ptime(date(1970, Jan, 1)));
            time[i] = diff.total_seconds();
            value[i]=Y[i];
            if(value[i] > max)
               max=value[i];
        }

        m_CustomPlot->graph(0)->setData(time, value);

        QVector<double> ytime(rain_size),ytime2(rain_size);
        for (int i=0; i<rain_size; i++){
            //timetmp[i]=(ptime_from_tm(rain[i].getTime())-ptime(date(1970, Jan, 1))).total_seconds();
            ytime[i]=YmMinVal;//YmMin->getValue();
            ytime2[i]=YmMinVal2;//YmMin2->getValue();
        }
        m_CustomPlot->graph(1)->setData(time, ytime);
        m_CustomPlot->graph(2)->setData(time, ytime2);

        QVector<double> yPoint(2),xPoint(2);

        yPoint[0]=YmMinVal;//YmMin->getValue();
        yPoint[1]=YmMinVal2;//YmMin2->getValue();
        xPoint[0]=(ptime_from_tm(YmMinTime)-ptime(date(1970, Jan, 1))).total_seconds();
        xPoint[1]=(ptime_from_tm(YmMinTime2)-ptime(date(1970, Jan, 1))).total_seconds();
        m_CustomPlot->graph(3)->setData(xPoint, yPoint);
        m_CustomPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
        m_CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
        //m_CustomPlot->setOpenGl(true);
        int graphnum=4;
        QVector<double> x(max), y(max);
        for (int j=0; j<activation_size; j++)
        {
            tm a1=activation[j].getStart();
            //a1.tm_mday-=1;
            //cout << a1.tm_mday<< " "<<a1.tm_mon<< " "<<a1.tm_year << endl;
            tm a2=activation[j].getEnd();
            // cout << a1.tm_mday<< " "<<a1.tm_mon<< " "<<a1.tm_year<< endl;
            //a2.tm_mday+=2;
            for (int k=0; k<2; k++)
            {
                //m_CustomPlot->addGraph();
                for (int i=0; i<(int)max; i++)
                {

                    if(k%2==0){

                        m_CustomPlot->graph( graphnum )->setPen( QPen( Qt::green) );

                        ptime tmp1 = ptime_from_tm(a1);
                        //ptime t11 = local_adj::utc_to_local(tmp1);

                        ptime utcepoch = ptime(date(1970, Jan, 1));
                        //ptime utcepoch1 = local_adj::utc_to_local(utcepoch);
                        //std::cout << (raindate-ptime(date(1970, Jan, 1))).total_milliseconds() << "\n";
                        boost::posix_time::time_duration diff =(tmp1-utcepoch);
                        //diff.total_milliseconds();
                        x[i] = diff.total_seconds();
                    }else{

                        m_CustomPlot->graph( graphnum )->setPen( QPen( Qt::blue) );
                        ptime tmp2 = ptime_from_tm(a2);
                        x[i] =(tmp2-ptime(date(1970, Jan, 1))).total_seconds();
                    }
                    y[i] = i;

                    //cout << x[i] << " "<< y[i]  << endl;
                }

                m_CustomPlot->graph(graphnum)->setData(x, y);
                // customPlot->graph(graphnum)->rescaleAxes(true);
                graphnum++;
            }


        }
        m_CustomPlot->replot();
    }
}

QCustomPlot* MainWindow::getPlotMobility(int indexTab, QString objName){
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QCustomPlot* tab = (QCustomPlot*)tabs->findChild<QCustomPlot*>("mobFunc"+objName);
    // QCustomPlot * m_CustomPlot = (QCustomPlot *) tab->widget(3);
    return tab;
}

QCustomPlot* MainWindow::getFitnessPlot(int indexTab){
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QCustomPlot* tab = (QCustomPlot*)tabs->findChild<QCustomPlot*>("fitFunc");
    // QCustomPlot * m_CustomPlot = (QCustomPlot *) tab->widget(3);
    return tab;
}
QCustomPlot* MainWindow::getKernelPlot(int indexTab){
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QCustomPlot* tab = (QCustomPlot*)tabs->findChild<QCustomPlot*>("kerFunc");
    // QCustomPlot * m_CustomPlot = (QCustomPlot *) tab->widget(3);
    return tab;
}

QCustomPlot* MainWindow::getKernelPlotRegression(int indexTab){
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QCustomPlot* tab = (QCustomPlot*)tabs->findChild<QCustomPlot*>("FuncPlot");
    // QCustomPlot * m_CustomPlot = (QCustomPlot *) tab->widget(3);
    return tab;
}

QCustomPlot* MainWindow::getAUCROCPlot(int indexTab){
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QCustomPlot* tab = (QCustomPlot*)tabs->findChild<QCustomPlot*>("AUCROC");
    // QCustomPlot * m_CustomPlot = (QCustomPlot *) tab->widget(3);
    return tab;
}


void MainWindow::updateMobilityKernelPlot(QCustomPlot *customPlot)
{


}

void MainWindow::closeTab(int index)
{
    //rilasciare lock
    mutex.lock();
    cout << "chiudere" << index << endl;
    ui->tabWidget_2->removeTab(index);
    MainWindow::threads.erase(MainWindow::threads.begin()+index);
    mutex.unlock();
}

void MainWindow::pushBackThread(QThread *thread)
{
    MainWindow::threads.push_back(thread);

}

void MainWindow::addTab(QString name, Rain * rain, int rain_size, Activation *activation, int activation_size,QString fitnessType)
{
    QTabWidget * tabwidget = new QTabWidget();
    tabwidget->setObjectName("tabwidget");
    QCustomPlot * customPlot = new QCustomPlot();
    //customPlot->setOpenGl(true,64);
    QCustomPlot * mobFunc = new QCustomPlot();
    QCustomPlot * kerFunc = new QCustomPlot();
    int indextab= ui->tabWidget_2->addTab(tabwidget, name);
    QWidget * tab1=ui->tabWidget_2->widget(ui->tabWidget_2->count()-1);
    QVBoxLayout * mainL = new QVBoxLayout();

    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spUp.setVerticalStretch(2);
    QVBoxLayout * vertical = new QVBoxLayout();
    QSplitter * splitter = new QSplitter();
    MainWindow::makeFitnessPlot(customPlot);
    customPlot->setSizePolicy(spUp);
    customPlot->setObjectName("fitFunc");
    splitter->addWidget(customPlot);
    MainWindow::makeKernelPlot(kerFunc,this);
    kerFunc->setSizePolicy(spUp);
    kerFunc->setObjectName("kerFunc");
    kerFunc->plotLayout()->insertRow(0);
    kerFunc->plotLayout()->addElement(0, 0, new QCPPlotTitle(kerFunc, "Best kernel of current iteration (Bkci)"));
    splitter->addWidget(kerFunc);
    MainWindow::makeMobilityFunctionPlot(mobFunc, rain,  rain_size, activation, activation_size);
    mobFunc->setSizePolicy(spUp);

    mobFunc->setObjectName("mobFunc");
    //mobFunc->rescaleAxes();
    splitter->addWidget(mobFunc);

    splitter->setOrientation(Qt::Vertical);

    vertical->addWidget(splitter);
    //vertical->addStretch(vertical->sizeConstraint()*2);


    mainL->addLayout(vertical);
    QGridLayout * grid = new QGridLayout();


    QLabel * AbsMaxFit = new QLabel();
    AbsMaxFit->setText("Absolute Maximum Fitness (AMF):");
    grid->addWidget(AbsMaxFit,0,0);
    QLabel * AbsMaxFitNum = new QLabel();
    AbsMaxFitNum->setText("0");
    AbsMaxFitNum->setObjectName("AbsMaxFitNum");
    grid->addWidget(AbsMaxFitNum,0,1);

    QLabel * firstOccurenceText = new QLabel();
    QString fo = QString("Iteration of first occurence of AMF : %1").arg(0);
    firstOccurenceText->setText(fo);
    firstOccurenceText->setObjectName("firstOccurenceText");
    grid->addWidget(firstOccurenceText,0,2);



    QLabel * AbsAveFit = new QLabel();
    AbsAveFit->setText("Absolute Average Fitness:");
    grid->addWidget(AbsAveFit,1,0);
    QLabel * AbsAveFitNum = new QLabel();
    AbsAveFitNum->setText("0");
    AbsAveFitNum->setObjectName("AbsAveFitNum");
    grid->addWidget(AbsAveFitNum,1,1);

    QLabel * space1 = new QLabel();
    space1->setText(" ");
    grid->addWidget(space1,2,0);


    QLabel * gen = new QLabel();
    gen->setText("Current Iteration:");
    grid->addWidget(gen,3,0);
    QLabel * genNum = new QLabel();
    genNum->setText("0");
    genNum->setObjectName("GenerationText");
    grid->addWidget(genNum,3,1);

    QLabel * curAveFit = new QLabel();
    curAveFit->setText("Current Average Fitness:");
    grid->addWidget(curAveFit,4,0);
    QLabel * curAveFitNum = new QLabel();
    curAveFitNum->setText("0");
    curAveFitNum->setObjectName("curAveFitNum");
    grid->addWidget(curAveFitNum,4,1);

    QLabel * space = new QLabel();
    space->setText(" ");
    grid->addWidget(space,5,0);

    QLabel * bestIndiv = new QLabel();
    bestIndiv->setText("Best Individual of current iteration");
    grid->addWidget(bestIndiv,6,0);

    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText("Fitness using "+fitnessType+ " :");
    grid->addWidget(curMaxFit,7,0);
    QLabel * curMaxFitNum = new QLabel();
    curMaxFitNum->setText("0");
    curMaxFitNum->setObjectName("curMaxFitNum");
    grid->addWidget(curMaxFitNum,7,1);

    QLabel * tb = new QLabel();
    tb->setText("tb:");
    grid->addWidget(tb,8,0);
    QLabel * tbNum = new QLabel();
    tbNum->setText("0");
    tbNum->setObjectName("tbNum");
    grid->addWidget(tbNum,8,1);

    QLabel * dCritico = new QLabel();
    dCritico->setText("Safety margin:");
    grid->addWidget(dCritico,8,2);
    QLabel * dCriticoNum = new QLabel();
    dCriticoNum->setText("0");
    dCriticoNum->setObjectName("dCriticoNum");
    grid->addWidget(dCriticoNum,8,3);

    QLabel * momPrimo = new QLabel();
    momPrimo->setText("First-order momentum:");
    grid->addWidget(momPrimo,8,4);
    QLabel * momPrimoNum = new QLabel();
    momPrimoNum->setText("0");
    momPrimoNum->setObjectName("momPrimoNum");
    grid->addWidget(momPrimoNum,8,5);

    QLabel * zjmin = new QLabel();
    zjmin->setText("zj-min");
    grid->addWidget(zjmin,8,6);
    QLabel * zjminNum = new QLabel();
    zjminNum->setText("0");
    zjminNum->setObjectName("ZjminNum");
    grid->addWidget(zjminNum,8,7);

    QLabel * zcr = new QLabel();
    zcr->setText("zcr");
    grid->addWidget(zcr,8,8);
    QLabel * zcrNum = new QLabel();
    zcrNum->setText("0");
    zcrNum->setObjectName("ZcrNum");
    grid->addWidget(zcrNum,8,9);

    // first occurence at N iteration;


    mainL->addLayout(grid);

    QHBoxLayout * buttons = new QHBoxLayout();
    QProgressBar* bar = new QProgressBar();
    bar->setValue(0);
    bar->setObjectName("bar");
    buttons->addWidget(bar);
    //    connect(stop, SIGNAL (clicked()),this, SLOT (clickedStopButton()));
    ////    QPushButton* pause = new QPushButton();
    ////    pause->setText("Pause");
    ////    buttons->addWidget(pause);

    mainL->addLayout(buttons);
    tab1->setLayout(mainL);
    ui->tabWidget_2->setCurrentIndex(indextab);
}


void MainWindow::addTabAUCROC(QString name, Rain * rain, int rain_size, Activation *activation, int activation_size, QString fitnessType)
{
    QTabWidget * tabwidget = new QTabWidget();
    tabwidget->setObjectName("tabwidget");
    QCustomPlot * customPlot = new QCustomPlot();
    //customPlot->setOpenGl(true,64);
    QCustomPlot * mobFunc = new QCustomPlot();
    QCustomPlot * kerFunc = new QCustomPlot();
    int indextab= ui->tabWidget_2->addTab(tabwidget, name);
    QWidget * tab1=ui->tabWidget_2->widget(ui->tabWidget_2->count()-1);
    QVBoxLayout * mainL = new QVBoxLayout();


    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spUp.setVerticalStretch(2);
    QVBoxLayout * vertical = new QVBoxLayout();
    QSplitter * splitter = new QSplitter();
    MainWindow::makeFitnessPlot(customPlot);
    customPlot->setSizePolicy(spUp);
    customPlot->setObjectName("fitFunc");
    splitter->addWidget(customPlot);
    MainWindow::makeKernelPlot(kerFunc,this);
    kerFunc->setSizePolicy(spUp);
    kerFunc->setObjectName("kerFunc");
    kerFunc->plotLayout()->insertRow(0);
    kerFunc->plotLayout()->addElement(0, 0, new QCPPlotTitle(kerFunc, "Best kernel of current iteration (Bkci)"));
    splitter->addWidget(kerFunc);
    MainWindow::makeMobilityFunctionPlot(mobFunc, rain,  rain_size, activation, activation_size);
    mobFunc->setSizePolicy(spUp);

    mobFunc->setObjectName("mobFunc");
    //mobFunc->rescaleAxes();
    splitter->addWidget(mobFunc);

    splitter->setOrientation(Qt::Vertical);

    QSplitter * splitterHorizontal = new QSplitter();
    splitterHorizontal->setOrientation(Qt::Horizontal);

    splitterHorizontal->addWidget(splitter);
    splitterHorizontal->setStretchFactor(0, 4);
    //PLOT AUC ROC Con scritte


    //splitterHorizontal->addWidget();
    QSizePolicy spHo(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spHo.setHorizontalStretch(0.5);

    QVBoxLayout * rightside = new QVBoxLayout();


    QGridLayout * gridAUC = new QGridLayout();

    QCustomPlot * AUCROCPlot = new QCustomPlot();
    MainWindow::makeAUCROCPlot(AUCROCPlot);
    AUCROCPlot->setSizePolicy(spHo);
    AUCROCPlot->setObjectName("AUCROC");
    rightside->addWidget(AUCROCPlot,1.5);
    //gridAUC->addWidget(AUCROCPlot,0,0);




    QLabel * AUC = new QLabel();
    AUC->setText("Area under curve (AUC) :");
    gridAUC->addWidget(AUC,0,0);
    QLabel * AUCValue = new QLabel();
    AUCValue->setText("0");
    AUCValue->setObjectName("AUCValue");
    gridAUC->addWidget(AUCValue,0,1);
    rightside->addLayout(gridAUC);


    QCustomPlot * DETPlot = new QCustomPlot();
    MainWindow::makeDETPlot(DETPlot);
    DETPlot->setSizePolicy(spHo);
    DETPlot->setObjectName("DET");
    rightside->addWidget(DETPlot,1.5);

    auto widget = new QWidget();
    widget->setLayout(rightside);


    splitterHorizontal->addWidget(widget);
    splitterHorizontal->setStretchFactor(1, 1);
    vertical->addWidget(splitterHorizontal);
    vertical->setStretch(0,2);
    //vertical->addStretch(vertical->sizeConstraint()*2);


    mainL->addLayout(vertical);

    QGridLayout * grid = new QGridLayout();


    QLabel * AbsMaxFit = new QLabel();
    AbsMaxFit->setText("Absolute Maximum Fitness (AMF) :");
    grid->addWidget(AbsMaxFit,0,0);
    QLabel * AbsMaxFitNum = new QLabel();
    AbsMaxFitNum->setText("0");
    AbsMaxFitNum->setObjectName("AbsMaxFitNum");
    grid->addWidget(AbsMaxFitNum,0,1);

    QLabel * firstOccurenceText = new QLabel();
    QString fo = QString("Iteration of first occurence of AMF : %1").arg(0);
    firstOccurenceText->setText(fo);
    firstOccurenceText->setObjectName("firstOccurenceText");
    grid->addWidget(firstOccurenceText,0,2);



    QLabel * AbsAveFit = new QLabel();
    AbsAveFit->setText("Absolute Average Fitness:");
    grid->addWidget(AbsAveFit,1,0);
    QLabel * AbsAveFitNum = new QLabel();
    AbsAveFitNum->setText("0");
    AbsAveFitNum->setObjectName("AbsAveFitNum");
    grid->addWidget(AbsAveFitNum,1,1);

    QLabel * space1 = new QLabel();
    space1->setText(" ");
    grid->addWidget(space1,2,0);


    QLabel * gen = new QLabel();
    gen->setText("Current Iteration:");
    grid->addWidget(gen,3,0);
    QLabel * genNum = new QLabel();
    genNum->setText("0");
    genNum->setObjectName("GenerationText");
    grid->addWidget(genNum,3,1);

    QLabel * curAveFit = new QLabel();
    curAveFit->setText("Current Average Fitness:");
    grid->addWidget(curAveFit,4,0);
    QLabel * curAveFitNum = new QLabel();
    curAveFitNum->setText("0");
    curAveFitNum->setObjectName("curAveFitNum");
    grid->addWidget(curAveFitNum,4,1);

    QLabel * space = new QLabel();
    space->setText(" ");
    grid->addWidget(space,5,0);

    QLabel * bestIndiv = new QLabel();
    bestIndiv->setText("Best Individual of current iteration");
    grid->addWidget(bestIndiv,6,0);

    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText("Fitness using "+ fitnessType+" :");
    grid->addWidget(curMaxFit,7,0);
    QLabel * curMaxFitNum = new QLabel();
    curMaxFitNum->setText("0");
    curMaxFitNum->setObjectName("curMaxFitNum");
    grid->addWidget(curMaxFitNum,7,1);

    QLabel * tb = new QLabel();
    tb->setText("tb:");
    grid->addWidget(tb,8,0);
    QLabel * tbNum = new QLabel();
    tbNum->setText("0");
    tbNum->setObjectName("tbNum");
    grid->addWidget(tbNum,8,1);

    QLabel * dCritico = new QLabel();
    dCritico->setText("Safety margin:");
    grid->addWidget(dCritico,8,2);
    QLabel * dCriticoNum = new QLabel();
    dCriticoNum->setText("0");
    dCriticoNum->setObjectName("dCriticoNum");
    grid->addWidget(dCriticoNum,8,3);

    QLabel * momPrimo = new QLabel();
    momPrimo->setText("First-order momentum:");
    grid->addWidget(momPrimo,8,4);
    QLabel * momPrimoNum = new QLabel();
    momPrimoNum->setText("0");
    momPrimoNum->setObjectName("momPrimoNum");
    grid->addWidget(momPrimoNum,8,5);

    QLabel * Zjmin = new QLabel();
    Zjmin->setText("Zj-min");
    grid->addWidget(Zjmin,8,6);
    QLabel * ZjminNum = new QLabel();
    ZjminNum->setText("0");
    ZjminNum->setObjectName("ZjminNum");
    grid->addWidget(ZjminNum,8,7);

    QLabel * Zcr = new QLabel();
    Zcr->setText("Zcr");
    grid->addWidget(Zcr,8,8);
    QLabel * ZcrNum = new QLabel();
    ZcrNum->setText("0");
    ZcrNum->setObjectName("ZcrNum");
    grid->addWidget(ZcrNum,8,9);



    // first occurence at N iteration;


    mainL->addLayout(grid);

    QHBoxLayout * buttons = new QHBoxLayout();
    QProgressBar* bar = new QProgressBar();
    bar->setValue(0);
    bar->setObjectName("bar");
    buttons->addWidget(bar);
    //    connect(stop, SIGNAL (clicked()),this, SLOT (clickedStopButton()));
    ////    QPushButton* pause = new QPushButton();
    ////    pause->setText("Pause");
    ////    buttons->addWidget(pause);

    mainL->addLayout(buttons);
    tab1->setLayout(mainL);
    ui->tabWidget_2->setCurrentIndex(indextab);
}

void MainWindow::addTabRegression(QString name,int numberofFunction)
{
    QTabWidget * tabwidget = new QTabWidget();
    tabwidget->setObjectName("tabRegression");
    //QCustomPlot * customPlot = new QCustomPlot();
    //customPlot->setOpenGl(true,64);

    QCustomPlot * kerFunc = new QCustomPlot();
    int indextab= ui->tabWidget_2->addTab(tabwidget, name);
    QWidget * tab1=ui->tabWidget_2->widget(ui->tabWidget_2->count()-1);
    QVBoxLayout * mainL = new QVBoxLayout();

    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spUp.setVerticalStretch(2);
    QVBoxLayout * vertical = new QVBoxLayout();
//    QSplitter * splitter = new QSplitter();
    //MainWindow::makeFitnessPlot(customPlot);
    //customPlot->setSizePolicy(spUp);
    //customPlot->setObjectName("fitFunc");
    //splitter->addWidget(customPlot);




   // MainWindow::makeKernelPlot(kerFunc,this);
    kerFunc ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom);
    kerFunc->addGraph();
    kerFunc->graph(0)->setPen( QPen( Qt::red ) );
    kerFunc->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    kerFunc->addGraph();
    kerFunc->graph(1)->setPen( QPen( Qt::green ) );
    kerFunc->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    for (int i = 0; i < numberofFunction; ++i) {
        kerFunc->addGraph();
        kerFunc->graph(i+2)->setPen( QPen( Qt::blue ) );
    }

    kerFunc->setSizePolicy(spUp);
    kerFunc->setObjectName("FuncPlot");
    kerFunc->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(kerFunc, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestKernel(QPoint)));


//    splitter->addWidget(kerFunc);


//    splitter->setOrientation(Qt::Vertical);

    vertical->addWidget(kerFunc);
    vertical->addStretch(vertical->sizeConstraint()*2);


    mainL->addLayout(vertical);
    QGridLayout * grid = new QGridLayout();


    QLabel * AbsMaxFit = new QLabel();
    AbsMaxFit->setText("Absolute Maximum Fitness (AMF) :");
    grid->addWidget(AbsMaxFit,0,0);
    QLabel * AbsMaxFitNum = new QLabel();
    AbsMaxFitNum->setText("0");
    AbsMaxFitNum->setObjectName("AbsMaxFitNum");
    grid->addWidget(AbsMaxFitNum,0,1);

    QLabel * firstOccurenceText = new QLabel();
    QString fo = QString("Iteration of first occurence of AMF : %1").arg(0);
    firstOccurenceText->setText(fo);
    firstOccurenceText->setObjectName("firstOccurenceText");
    grid->addWidget(firstOccurenceText,0,2);

    QVBoxLayout * vertical2 = new QVBoxLayout();

    QTableWidget *tableResult = new QTableWidget();
    tableResult->setColumnCount(5);
    QStringList m_TableHeader;
    m_TableHeader<<"N."<<" w "<<" a "<< " b " << " t ";
    tableResult->setHorizontalHeaderLabels(m_TableHeader);
    tableResult->verticalHeader()->setVisible(false);
    tableResult->setRowCount(4);
    tableResult->setObjectName("tableResult");

//    tableResult->resizeColumnsToContents();
//    tableResult->setLayout(vertical2);
//    vertical2->addWidget(tableResult);
//    addRow(tableResult,
//           0,
//           "8",
//           "1",
//           "200 ",
//           "200");
    cout << "tableResult->horizontalHeader()->width() = " << tableResult->horizontalHeader()->width()<< endl;
    tableResult->setMinimumWidth(530);
    tableResult->setMaximumWidth(530);
    QLabel * t1 = new QLabel();
    t1->setText("Best Functions Parameters:");
    t1->setMinimumWidth(300);
    t1->setVisible(true);
    grid->addWidget(t1,0,3);
    grid->addWidget(tableResult,1,3,6,1);

    grid->addWidget(tableResult,1,3,6,1);
    QLabel * t = new QLabel();
    t->setText("");
    t->setMinimumWidth(300);
    t->setVisible(true);
    grid->addWidget(t,0,4);


    QLabel * AbsAveFit = new QLabel();
    AbsAveFit->setText("Absolute Average Fitness:");
    grid->addWidget(AbsAveFit,1,0);
    QLabel * AbsAveFitNum = new QLabel();
    AbsAveFitNum->setText("0");
    AbsAveFitNum->setObjectName("AbsAveFitNum");
    grid->addWidget(AbsAveFitNum,1,1);

    QLabel * space1 = new QLabel();
    space1->setText(" ");
    grid->addWidget(space1,2,0);


    QLabel * gen = new QLabel();
    gen->setText("Current Iteration:");
    grid->addWidget(gen,3,0);
    QLabel * genNum = new QLabel();
    genNum->setText("0");
    genNum->setObjectName("GenerationText");
    grid->addWidget(genNum,3,1);

    QLabel * curAveFit = new QLabel();
    curAveFit->setText("Current Average Fitness:");
    grid->addWidget(curAveFit,4,0);
    QLabel * curAveFitNum = new QLabel();
    curAveFitNum->setText("0");
    curAveFitNum->setObjectName("curAveFitNum");
    grid->addWidget(curAveFitNum,4,1);

    QLabel * space = new QLabel();
    space->setText(" ");
    grid->addWidget(space,5,0);

    QLabel * bestIndiv = new QLabel();
    bestIndiv->setText("Best Individual of current iteration");
    grid->addWidget(bestIndiv,6,0);

    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText("Fitness:");
    grid->addWidget(curMaxFit,7,0);
    QLabel * curMaxFitNum = new QLabel();
    curMaxFitNum->setText("0");
    curMaxFitNum->setObjectName("curMaxFitNum");
    grid->addWidget(curMaxFitNum,7,1);



//    QHBoxLayout * horizontal = new QHBoxLayout();
//    horizontal->addLayout(grid);
//    horizontal->addStretch(horizontal->sizeConstraint()*2);



//    QHBoxLayout * horizontal2 = new QHBoxLayout();
//    horizontal2->addWidget(tableResult);
//    horizontal2->addStretch(0.2);

//    horizontal->addLayout(horizontal2);

//    QVBoxLayout * vertical2 = new QVBoxLayout();
//    vertical2->addLayout(horizontal);



//    QLabel * tb = new QLabel();
//    tb->setText("tb:");
//    grid->addWidget(tb,8,0);
//    QLabel * tbNum = new QLabel();
//    tbNum->setText("0");
//    tbNum->setObjectName("tbNum");
//    grid->addWidget(tbNum,8,1);

//    QLabel * dCritico = new QLabel();
//    dCritico->setText("Safety margin:");
//    grid->addWidget(dCritico,8,2);
//    QLabel * dCriticoNum = new QLabel();
//    dCriticoNum->setText("0");
//    dCriticoNum->setObjectName("dCriticoNum");
//    grid->addWidget(dCriticoNum,8,3);

//    QLabel * momPrimo = new QLabel();
//    momPrimo->setText("First-order momentum:");
//    grid->addWidget(momPrimo,8,4);
//    QLabel * momPrimoNum = new QLabel();
//    momPrimoNum->setText("0");
//    momPrimoNum->setObjectName("momPrimoNum");
//    grid->addWidget(momPrimoNum,8,5);


//    // first occurence at N iteration;


    mainL->addLayout(grid);

    QHBoxLayout * buttons = new QHBoxLayout();
    QProgressBar* bar = new QProgressBar();
    bar->setValue(0);
    bar->setObjectName("bar");
    buttons->addWidget(bar);
    //    connect(stop, SIGNAL (clicked()),this, SLOT (clickedStopButton()));
    ////    QPushButton* pause = new QPushButton();
    ////    pause->setText("Pause");
    ////    buttons->addWidget(pause);

    mainL->addLayout(buttons);
    tab1->setLayout(mainL);
    ui->tabWidget_2->setCurrentIndex(indextab);
}


void MainWindow::addTabValidation(QString name, Rain * rain, int rain_size, Activation *activation, int activation_size)
{
    QTabWidget * tabwidget = new QTabWidget();
    tabwidget->setObjectName("tabwidget");
    //customPlot->setOpenGl(true,64);
    QCustomPlot * mobFunc = new QCustomPlot();
    QCustomPlot * kerFunc = new QCustomPlot();
    ui->tabWidget_2->addTab(tabwidget, name);
    QWidget * tab1=ui->tabWidget_2->widget(ui->tabWidget_2->count()-1);
    QVBoxLayout * mainL = new QVBoxLayout();

    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spUp.setVerticalStretch(2);
    QVBoxLayout * vertical = new QVBoxLayout();
    MainWindow::makeKernelPlot(kerFunc, this);
    kerFunc->setSizePolicy(spUp);
    kerFunc->setObjectName("kerFunc");
    vertical->addWidget(kerFunc);
    MainWindow::makeMobilityFunctionPlot(mobFunc, rain,  rain_size, activation, activation_size);
    mobFunc->setSizePolicy(spUp);

    mobFunc->setObjectName("mobFunc");
    //mobFunc->rescaleAxes();
    vertical->addWidget(mobFunc);


    vertical->addStretch(vertical->sizeConstraint()*2);
    mainL->addLayout(vertical);
    QGridLayout * grid = new QGridLayout();


    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText("Fitness:");
    grid->addWidget(curMaxFit,0,0);
    QLabel * curMaxFitNum = new QLabel();
    curMaxFitNum->setText("0");
    curMaxFitNum->setObjectName("curMaxFitNum");
    grid->addWidget(curMaxFitNum,0,1);


    QLabel * tb = new QLabel();
    tb->setText("tb:");
    grid->addWidget(tb,1,0);
    QLabel * tbNum = new QLabel();
    tbNum->setText("0");
    tbNum->setObjectName("tbNum");
    grid->addWidget(tbNum,1,1);

    QLabel * dCritico = new QLabel();
    dCritico->setText("Safety margin:");
    grid->addWidget(dCritico,1,2);
    QLabel * dCriticoNum = new QLabel();
    dCriticoNum->setText("0");
    dCriticoNum->setObjectName("dCriticoNum");
    grid->addWidget(dCriticoNum,1,3);

    QLabel * momPrimo = new QLabel();
    momPrimo->setText("First-order momentum:");
    grid->addWidget(momPrimo,1,4);
    QLabel * momPrimoNum = new QLabel();
    momPrimoNum->setText("0");
    momPrimoNum->setObjectName("momPrimoNum");
    grid->addWidget(momPrimoNum,1,5);


    // first occurence at N iteration;


    mainL->addLayout(grid);

    tab1->setLayout(mainL);
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-1);
}


QLayout* wrap(QWidget* w){
    auto layout = new QVBoxLayout();
    layout->addWidget( w );
    return layout;
}
QWidget* wrap(QLayout* l){
    auto widget = new QWidget();
    widget->setLayout( l );
    return widget;
}

void MainWindow::getGraphs(QString nameKerFunc,QString nameMobFunc,QString fitness, auto* mainL, Rain* rain, int rain_size, int activation_size, Activation *activation, QCustomPlot* mobFunc)
{
    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spUp.setVerticalStretch(4);
    QVBoxLayout * vertical = new QVBoxLayout();
    MainWindow::makeMobilityFunctionPlot(mobFunc, rain,  rain_size, activation, activation_size);
    mobFunc->setSizePolicy(spUp);

    mobFunc->setObjectName("mobFunc"+nameMobFunc);
    //mobFunc->rescaleAxes();
    vertical->addWidget(mobFunc);

    //vertical->setStretch(0,2);
//    vertical->addStretch(vertical->sizeConstraint()*8);
   // mainL->addStretch(mainL->sizeConstraint()*8);
    mainL->addWidget(wrap(vertical));

    mainL->setStretch(0,5);
    QGridLayout * grid = new QGridLayout();

    QLabel * curMaxFitGMDn = new QLabel();
    curMaxFitGMDn->setText("Fitness HW");
    grid->addWidget(curMaxFitGMDn,1,0);
    QLabel * curMaxFitNumGMDn = new QLabel();
    curMaxFitNumGMDn->setText("0");
    curMaxFitNumGMDn->setObjectName("curMaxFitNumGMDn");
    grid->addWidget(curMaxFitNumGMDn,1,1);

    QLabel * curMaxFitEW = new QLabel();
    curMaxFitEW->setText("Fitness EW");
    grid->addWidget(curMaxFitEW,2,0);
    QLabel * curMaxFitNumEW = new QLabel();
    curMaxFitNumEW->setText("0");
    curMaxFitNumEW->setObjectName("curMaxFitNumEW");
    grid->addWidget(curMaxFitNumEW,2,1);

    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText(fitness);
    grid->addWidget(curMaxFit,3,0);
    QLabel * curMaxFitNum = new QLabel();
    curMaxFitNum->setText("0");
    curMaxFitNum->setObjectName("curMaxFitNum"+nameMobFunc);
    grid->addWidget(curMaxFitNum,3,1);

//    QLabel * curMaxFitGMD = new QLabel();
//    curMaxFitGMD->setText("Fitness GMD");
//    grid->addWidget(curMaxFitGMD,1,0);
//    QLabel * curMaxFitNumGMD = new QLabel();
//    curMaxFitNumGMD->setText("0");
//    curMaxFitNumGMD->setObjectName("curMaxFitNumGMD");
//    grid->addWidget(curMaxFitNumGMD,1,1);




    QLabel * tb = new QLabel();
    tb->setText("tb:");
    grid->addWidget(tb,4,0);
    QLabel * tbNum = new QLabel();
    tbNum->setText("0");
    tbNum->setObjectName("tbNum"+nameMobFunc);
    grid->addWidget(tbNum,4,1);

    QLabel * dCritico = new QLabel();
    dCritico->setText("Safety margin:");
    grid->addWidget(dCritico,4,2);
    QLabel * dCriticoNum = new QLabel();
    dCriticoNum->setText("0");
    dCriticoNum->setObjectName("dCriticoNum"+nameMobFunc);
    grid->addWidget(dCriticoNum,4,3);

    QLabel * momPrimo = new QLabel();
    momPrimo->setText("First-order momentum:");
    grid->addWidget(momPrimo,4,4);
    QLabel * momPrimoNum = new QLabel();
    momPrimoNum->setText("0");
    momPrimoNum->setObjectName("momPrimoNum"+nameMobFunc);
    grid->addWidget(momPrimoNum,4,5);


    QLabel * zjmin = new QLabel();
    zjmin->setText("zj-min");
    grid->addWidget(zjmin,4,6);
    QLabel * zjminNum = new QLabel();
    zjminNum->setText("0");
    zjminNum->setObjectName("ZjminNum");
    grid->addWidget(zjminNum,4,7);

    QLabel * zcr = new QLabel();
    zcr->setText("zcr");
    grid->addWidget(zcr,4,8);
    QLabel * zcrNum = new QLabel();
    zcrNum->setText("0");
    zcrNum->setObjectName("ZcrNum");
    grid->addWidget(zcrNum,4,9);

    // first occurence at N iteration;
    // GMD--------------------------

    mainL->addWidget(wrap(grid));
}

void MainWindow::addTabValidationNewInterface(QString name, Rain * rain, int rain_size, Activation *activation, int activation_size)
{
    QTabWidget * tabwidget = new QTabWidget();
    tabwidget->setObjectName("tabwidget");
    //customPlot->setOpenGl(true,64);
    QCustomPlot * mobFuncGMD = new QCustomPlot();
    QCustomPlot * mobFuncGMDn = new QCustomPlot();
    QCustomPlot * mobFuncEW = new QCustomPlot();
    QCustomPlot * mobFuncAUCROC = new QCustomPlot();
    QCustomPlot * kerFunc = new QCustomPlot();
    ui->tabWidget_2->addTab(tabwidget, name);
    QWidget * tab1=ui->tabWidget_2->widget(ui->tabWidget_2->count()-1);


    QSplitter* horizontalSplitter = new QSplitter();
    horizontalSplitter->setOrientation(Qt::Vertical);

    //Kernel plot
    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spUp.setVerticalStretch(2);
    QVBoxLayout * vertical = new QVBoxLayout();
    MainWindow::makeKernelPlot(kerFunc, this);
    kerFunc->plotLayout()->insertRow(0);
    kerFunc->plotLayout()->addElement(0, 0, new QCPPlotTitle(kerFunc, "Operative Kernel"));


    kerFunc->setSizePolicy(spUp);
    kerFunc->setObjectName("kerFunc");
    vertical->addWidget(kerFunc);

    horizontalSplitter->addWidget(wrap(vertical));


//    QSplitter* verticalSplitterGMDeGMDn = new QSplitter();
//    verticalSplitterGMDeGMDn->setOrientation(Qt::Horizontal);
//    //GMD ------------------------------------
//    QVBoxLayout * mainLGMD = new QVBoxLayout();
//    getGraphs("kerFunc","GMD","Fitness GMD :", mainLGMD, rain, rain_size, activation_size, activation, mobFuncGMD);

//    verticalSplitterGMDeGMDn->addWidget(wrap(mainLGMD));

    //GMDn ------------------------------------
//    QVBoxLayout * mainLGMDn = new QVBoxLayout();
//    getGraphs("kerFunc","GMDn","Fitness GMDn :", mainLGMDn, rain, rain_size, activation_size, activation, mobFuncGMDn);

//    verticalSplitterGMDeGMDn->addWidget(wrap(mainLGMDn));

//    horizontalSplitter->addWidget(verticalSplitterGMDeGMDn);

//    QSplitter* verticalSplitterEW = new QSplitter();
//    verticalSplitterEW->setOrientation(Qt::Horizontal);

    //EW ------------------------------------
//    QVBoxLayout * mainLEW = new QVBoxLayout();
//    getGraphs("kerFunc","EW","Fitness EW :", mainLEW, rain, rain_size, activation_size, activation, mobFuncEW);


//    verticalSplitterEW->addWidget(wrap(mainLEW));

    QSplitter * rightside = new QSplitter();
    QVBoxLayout * mainLAUCROC = new QVBoxLayout();
    rightside->setOrientation(Qt::Vertical);
    getGraphs("kerFunc","AUCROC","Fitness AUCROC :", mainLAUCROC, rain, rain_size, activation_size, activation, mobFuncAUCROC);
    rightside->addWidget(wrap(mainLAUCROC));

    QGridLayout * gridAUC = new QGridLayout();

    QCustomPlot * AUCROCPlot = new QCustomPlot();
    MainWindow::makeAUCROCPlot(AUCROCPlot);
    //AUCROCPlot->setSizePolicy(spHo);
    AUCROCPlot->setObjectName("AUCROC");
    gridAUC->addWidget(AUCROCPlot,0,0);
    //gridAUC->addWidget(AUCROCPlot,0,0);

    QCustomPlot * DETPlot = new QCustomPlot();
    MainWindow::makeDETPlot(DETPlot);
    //DETPlot->setSizePolicy(spHo);
    DETPlot->setObjectName("DET");
    gridAUC->addWidget(DETPlot,0,1);

    QLabel * AUC = new QLabel();
    AUC->setText("Area under curve (AUC) :");
    gridAUC->addWidget(AUC,1,0);
    QLabel * AUCValue = new QLabel();
    AUCValue->setText("0");
    AUCValue->setObjectName("AUCValue");
    gridAUC->addWidget(AUCValue,1,1);

    gridAUC->setRowStretch(0,1.5);
//rightside->setStretchFactor(0,2);

    rightside->addWidget(wrap(gridAUC));

//    verticalSplitterEW->addWidget(rightside);

//    horizontalSplitter->addWidget(verticalSplitterEW);
    horizontalSplitter->addWidget(rightside);
    tab1->setLayout(wrap(horizontalSplitter));
    ui->tabWidget_2->setCurrentIndex(ui->tabWidget_2->count()-1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newCalibrationProject_triggered()
{
    Dialog *dialog = new Dialog();
    dialog->setReadOnlyProjName(false);
    dialog->setMainWindow(this);
    dialog->show();
}

void MainWindow::myClick(QTreeWidgetItem *item, int column)
{
    QVariantList listParameter = xmlmanager->getAllElementsFromProjectName(item->data(0,Qt::UserRole).toString());
    QTreeWidgetItem * p = item->parent();
//    int i = ui->treeWidget->indexOfTopLevelItem(item);
   // cout << column << endl;
//    cout << item->parent()->text(column).toStdString() << endl;
    if(ui->treeWidget->indexOfTopLevelItem(item) <= -1 && QString::compare(item->parent()->text(column), "Calibration", Qt::CaseInsensitive)==0){
        if(listParameter.size() > 5){
            Dialog *dialog = new Dialog();
            dialog->setReadOnlyProjName(true);
            dialog->setParameters(listParameter);
            dialog->setMainWindow(this);
            dialog->show();
        }
    }else
        if(ui->treeWidget->indexOfTopLevelItem(item) <= -1 && QString::compare(item->parent()->text(column), "Validation", Qt::CaseInsensitive)==0){
            if(listParameter.size() > 5){
                Validation *validation = new Validation();
                validation->setReadOnlyProjName(true);
                validation->setParameters(listParameter);
                validation->setMainWindow(this);
                validation->show();
            }
        }
        else
                if(ui->treeWidget->indexOfTopLevelItem(item) <= -1 && QString::compare(item->parent()->text(column), "Regression", Qt::CaseInsensitive)==0){
                    if(listParameter.size() > 5){
                        Regression *regression = new Regression();
//                        regression->setReadOnlyProjName(true);
                        regression->setW(this);
                        regression->setReadOnlyProjName(true);
                        regression->setParameters(listParameter);
                        regression->setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint
                                                   );
//                        regression->setMainWindow(this);
                        regression->show();
                    }
                }
}

void MainWindow::on_tabWidget_2_tabCloseRequested(int index)
{
    // button Stop

    //prendere lock
    if( dynamic_cast< SAKeController* >( (MainWindow::threads[index])) ){

        if(!((SAKeController*) MainWindow::threads[index])->isRunning()){
            mutex.lock();
            MainWindow::threads.erase(MainWindow::threads.begin()+index);
            ui->tabWidget_2->removeTab(index);
            mutex.unlock();
        }else
            if(!(((SAKeController*) MainWindow::threads[index])->getStop())){
                ((SAKeController*) MainWindow::threads[index])->setClickCloseTab(true);
                ((SAKeController*) MainWindow::threads[index])->stopThread();
            }
    }else
        if(dynamic_cast< ValidationController* >( (MainWindow::threads[index]))){
            if(!((ValidationController*) MainWindow::threads[index])->isRunning()){
                mutex.lock();
                MainWindow::threads.erase(MainWindow::threads.begin()+index);
                ui->tabWidget_2->removeTab(index);
                mutex.unlock();
            }
        }else
            if(dynamic_cast< RegressionController* >( (MainWindow::threads[index]))){
                if(!((RegressionController*) MainWindow::threads[index])->isRunning()){
                    mutex.lock();
                    MainWindow::threads.erase(MainWindow::threads.begin()+index);
                    ui->tabWidget_2->removeTab(index);
                    mutex.unlock();
                }else
                    if(!(((RegressionController*) MainWindow::threads[index])->getStop())){
                        ((RegressionController*) MainWindow::threads[index])->setClickCloseTab(true);
                        ((RegressionController*) MainWindow::threads[index])->stopThread();
                    }
            }
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::on_stopButton_triggered()
{
    if(ui->tabWidget_2->count()>0){
        int index = ((QTabWidget*)ui->tabWidget_2)->currentIndex();

        //if(ui->tabWidget_2->)

        if( dynamic_cast< SAKeController* >( MainWindow::threads[index] ) ){

            if(((SAKeController*) MainWindow::threads[index])->isRunning())
                if(!(((SAKeController*) MainWindow::threads[index])->getStop()))
                    ((SAKeController*) MainWindow::threads[index])->stopThread();

        }
    }
}

void MainWindow::on_actionNewValidationProject_triggered()
{
    Validation *validation = new Validation();
    validation->setMainWindow(this);
    validation->show();
}

void MainWindow::prepareMenu(const QPoint &pos)
{
    QAction *copy = new QAction(QIcon(""), tr("&Create a copy of the this project"), this);
    QAction *delAct = new QAction(QIcon(""), tr("&Delete Project"), this);
    QAction *show = new QAction(QIcon(""), tr("&Show Result"), this);
    QTreeWidgetItem *item = ui->treeWidget->itemAt( pos );
    connect(show, SIGNAL(triggered()),this, SLOT(openFolderProject()),Qt::UniqueConnection) ;
    connect(delAct, SIGNAL(triggered()),signalMapper, SLOT(map()),Qt::UniqueConnection) ;//
    connect(copy, SIGNAL(triggered()),signalMapperCopy, SLOT(map()),Qt::UniqueConnection) ;
    //this, deleteProject(QString));//item->data(0,Qt::UserRole).toString() });
    signalMapper -> setMapping(delAct,item->data(0,Qt::UserRole).toInt());
    signalMapperCopy -> setMapping(copy,(QObject*)item);
//    signalMapperCopy -> setMapping(item->,item->data(0,Qt::UserRole).toInt());
    connect(signalMapper, SIGNAL(mapped(int )), this, SLOT(deleteProject(int)),Qt::UniqueConnection) ;
    connect(signalMapperCopy, SIGNAL(mapped(QObject *)),this, SLOT(createProjectFromOneAlreadyExist(QObject *)),Qt::UniqueConnection) ;


    QMenu menu(this);
    menu.addAction(delAct);
    menu.addAction(show);

    menu.addAction(copy);
    menu.exec( ui->treeWidget->mapToGlobal(pos) );
}

void MainWindow::expandTreeViewSlot()
{
    ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0));
    ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(1));
    ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(2));
    //    ui->treeWidget->setExpanded(1,true);
    //    ui->treeWidget->setExpanded(2,true);
}

void MainWindow::resizeMobilityFunction()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("mobFunc");
    currentPlot->rescaleAxes();
    currentPlot->replot();

}

void MainWindow::savePngMobilityFunction()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("mobFunc");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save png"), "",
                                                   tr("Png (*.png);;All Files (*)"));
    currentPlot->savePng(fileName);
}

void MainWindow::savePdfMobilityFunction()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("mobFunc");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save pdf"), "",
                                                   tr("Pdf (*.pdf);;All Files (*)"));
    currentPlot->savePdf(fileName);
}

void MainWindow::resizeKernel()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("kerFunc");
    currentPlot->rescaleAxes();
    currentPlot->replot();
}

void MainWindow::resizeKernelRegression()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("FuncPlot");
    currentPlot->rescaleAxes();
    currentPlot->replot();
}

void MainWindow::savePngKernel()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("kerFunc");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save png"), "",
                                                   tr("Png (*.png);;All Files (*)"));
    currentPlot->savePng(fileName);
}

void MainWindow::savePdfKernel()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("kerFunc");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save pdf"), "",
                                                   tr("Pdf (*.pdf);;All Files (*)"));
    currentPlot->savePdf(fileName);
}

void MainWindow::resizeFitness()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("fitFunc");
    currentPlot->rescaleAxes();
    currentPlot->replot();
}

void MainWindow::savePngFitness()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("fitFunc");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save png"), "",
                                                   tr("Png (*.png);;All Files (*)"));
    currentPlot->savePng(fileName);
}

void MainWindow::savePdfFitness()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("fitFunc");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save pdf"), "",
                                                   tr("Pdf (*.pdf);;All Files (*)"));
    currentPlot->savePdf(fileName);
}


void MainWindow::resizeAUCROC()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("AUCROC");
    currentPlot->rescaleAxes();
    currentPlot->replot();
}

void MainWindow::savePngAUCROC()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("AUCROC");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save png"), "",
                                                   tr("Png (*.png);;All Files (*)"));
    currentPlot->savePng(fileName);
}

void MainWindow::savePdfAUCROC()
{
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("AUCROC");

    QString fileName =QFileDialog::getSaveFileName(this,
                                                   tr("Save pdf"), "",
                                                   tr("Pdf (*.pdf);;All Files (*)"));
    currentPlot->savePdf(fileName);
}

void MainWindow::contextMenuRequestMobilityFunction(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("mobFunc");

    menu->addAction("Rescale Axes", this, SLOT(resizeMobilityFunction()));
    menu->addAction("Save Graph PDF", this, SLOT(savePdfMobilityFunction()));
    menu->addAction("Save Graph PNG", this, SLOT(savePngMobilityFunction()));
    menu->popup(currentPlot->mapToGlobal(pos));

}

void MainWindow::contextMenuRequestKernel(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("kerFunc");

    menu->addAction("Rescale Axes", this, SLOT(resizeKernel()));
    menu->addAction("Save Graph PDF", this, SLOT(savePdfKernel()));
    menu->addAction("Save Graph PNG", this, SLOT(savePngKernel()));

    menu->popup(currentPlot->mapToGlobal(pos));

}

void MainWindow::contextMenuRequestKernelRegression(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("FuncPlot");

    menu->addAction("Rescale Axes", this, SLOT(resizeKernel()));
//    menu->addAction("Save Graph PDF", this, SLOT(savePdfKernel()));
//    menu->addAction("Save Graph PNG", this, SLOT(savePngKernel()));

    menu->popup(currentPlot->mapToGlobal(pos));

}

void MainWindow::contextMenuRequestFitness(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("fitFunc");

    menu->addAction("Rescale Axes", this, SLOT(resizeFitness()));
    menu->addAction("Save Graph PDF", this, SLOT(savePdfFitness()));
    menu->addAction("Save Graph PNG", this, SLOT(savePngFitness()));

    menu->popup(currentPlot->mapToGlobal(pos));

}

void MainWindow::contextMenuRequestAUCROC(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(((QTabWidget*)ui->tabWidget_2)->currentIndex());
    QCustomPlot* currentPlot= (QCustomPlot*)tabs->findChild<QCustomPlot*>("AUCROC");

    menu->addAction("Rescale Axes", this, SLOT(resizeAUCROC()));
    menu->addAction("Save Graph PDF", this, SLOT(savePdfAUCROC()));
    menu->addAction("Save Graph PNG", this, SLOT(savePngAUCROC()));

    menu->popup(currentPlot->mapToGlobal(pos));

}

void MainWindow::openFolderProject()
{
    QDesktopServices::openUrl(QUrl(xmlmanager->folderPath+"/workspace/calibration"));
}

void MainWindow::showAlertInputCsv(int row, QString filename, QString e)
{
    QString error = QString("Inside file : "+ filename+"\n");
    error += QString("Error at line: %1 \n").arg(row);
    error += QString("Error : "+ e);

    QMessageBox::information(
                this,
                tr(QString("Error input file").toStdString().c_str()),
                tr(error.toStdString().c_str()) );

}

void MainWindow::showLoadingWheel()
{
//    QLabel *lbl = new QLabel;
//    QMovie *movie = new QMovie(":/img/loader.gif");
//    lbl->setMovie(movie);
//    lbl->show();
//    movie->start();

}



void MainWindow::deleteProject(int item)
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Warning", "Are you sure you want to delete the project?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          xmlmanager->deleteProject(item);
          //item->parent()->setExpanded(true);

          xmlmanager->ReadCalibrationProjectXML();
          emit expandTreeViewSignals();
      }


}

void MainWindow::createProjectFromOneAlreadyExist(QObject * t)
{
    QTreeWidgetItem* item = (QTreeWidgetItem*) t;
    cout << item->data(0,Qt::UserRole).toInt() << endl;
    cout << ui->treeWidget->indexOfTopLevelItem(item) << endl;
    int column =0;

    QVariantList listParameter = xmlmanager->getAllElementsFromProjectName(item->data(0,Qt::UserRole).toString());
    QTreeWidgetItem * p = item->parent();
//    int i = ui->treeWidget->indexOfTopLevelItem(item);
    cout << column << endl;
//    cout << item->parent()->text(column).toStdString() << endl;
    if(ui->treeWidget->indexOfTopLevelItem(item) <= -1 && QString::compare(item->parent()->text(column), "Calibration", Qt::CaseInsensitive)==0){
        if(listParameter.size() > 5){
            Dialog *dialog = new Dialog();
            //dialog->setReadOnlyProjName(true);
            dialog->setParameters(listParameter);
            dialog->setMainWindow(this);
            dialog->show();
        }
    }else
        if(ui->treeWidget->indexOfTopLevelItem(item) <= -1 && QString::compare(item->parent()->text(column), "Validation", Qt::CaseInsensitive)==0){
            if(listParameter.size() > 5){
                Validation *validation = new Validation();
                //validation->setReadOnlyProjName(true);
                validation->setParameters(listParameter);
                validation->setMainWindow(this);
                validation->show();
            }
        }
        else
                if(ui->treeWidget->indexOfTopLevelItem(item) <= -1 && QString::compare(item->parent()->text(column), "Regression", Qt::CaseInsensitive)==0){
                    if(listParameter.size() > 5){
                        Regression *regression = new Regression();
//                        regression->setReadOnlyProjName(true);
                        regression->setW(this);
                        regression->setParameters(listParameter);
//                        regression->setMainWindow(this);
                        regression->show();
                    }
                }


}



XMLManager *MainWindow::getXmlmanager() const
{
    return xmlmanager;
}

void MainWindow::setXmlmanager(XMLManager *value)
{
    xmlmanager = value;
}

void MainWindow::on_actionNew_Regression_Project_triggered()
{
   Regression *r = new Regression(this);
   r->show();
}
