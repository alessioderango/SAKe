#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "validation.h"
#include "Regression.h"

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

    customPlot->addGraph();
    customPlot->graph( 1 )->setPen( QPen( Qt::green ) );
    //customPlot->graph( 1 )->setSelectedPen( QPen( Qt::blue, 2 ) );
    customPlot->graph( 1 )->setData( x1, y1 );

    // give the axes some labels:
    customPlot->xAxis->setLabel( "generation" );
    customPlot->yAxis->setLabel( "fitness" );
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange( 0, 20 );
    customPlot->yAxis->setRange( 0, 1.05 );

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestFitness(QPoint)));

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
}

void MainWindow::makeKernelPlot(QCustomPlot *customPlot,MainWindow * w)
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
    customPlot->addGraph();

    //add graph for preview kernel
    customPlot->addGraph();
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
    customPlot->graph(1)->setPen( QPen( Qt::green ) );
    customPlot->addGraph();


    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), w, SLOT(contextMenuRequestKernel(QPoint)));

}

void MainWindow::updateFitnessPlot(int indexTab, QVector<double> x, QVector<double> y, QVector<double> x1, QVector<double> y1)
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
        ((QCPBars*)m_CustomPlot->plottable(0))->setData(xKernel, yKernel);

        m_CustomPlot->graph(1)->setData(xControlpoints, yControlpoints);
        m_CustomPlot->replot();
    }

}

void MainWindow::updateKernelPlotRegressionWithControlPoints(QCustomPlot *m_CustomPlot,QVector<double> xControlpoints,QVector<double> yControlpoints )
{
    if (m_CustomPlot)
    {
        m_CustomPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 10));
        m_CustomPlot->graph(2)->setPen( QPen( Qt::red ) );
        m_CustomPlot->graph(2)->setData(xControlpoints, yControlpoints);
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
        QVector<double> FNR(TPR.size(),0);
        for (int i = 0; i < FNR.size(); ++i) {
                 FNR[i] = (double)(((double)1)-TPR[i]);
        }
        (m_CustomPlot->graph(0))->setData(FNR, FPR);

        m_CustomPlot->replot();
    }


    QLabel* text = (QLabel*)tabs->findChild<QLabel*>("AUCValue");
    text->setText(QString("%1").arg(AUCROC));
    mutex.unlock();
}

void MainWindow::updateTexts(int indexTab,
                             QString s,
                             QString fitness,
                             QString cuavfitness,
                             QString tb,
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
    QLabel* safetyMArginL = (QLabel*)tabs->findChild<QLabel*>("dCriticoNum");
    safetyMArginL->setText(safetyMargin);

    QLabel* momentumL = (QLabel*)tabs->findChild<QLabel*>("momPrimoNum");
    momentumL->setText(momentum);

    QLabel* bestfndatItera = (QLabel*)tabs->findChild<QLabel*>("firstOccurenceText");
    QString fo = QString("First occurence of AMF at iteration: %1").arg(firstOccurence);
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

void MainWindow::updateTextsValidationAllInOne(int indexTab,QString name, QString fitness, QString tb, QString safetyMargin, QString momentum)
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
    //cout << "chiudere" << index << endl;
    ui->tabWidget_2->removeTab(index);
    MainWindow::threads.erase(MainWindow::threads.begin()+index);
    mutex.unlock();
}

void MainWindow::pushBackThread(QThread *thread)
{
    MainWindow::threads.push_back(thread);

}

void MainWindow::addTab(QString name, Rain * rain, int rain_size, Activation *activation, int activation_size)
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
    AbsMaxFit->setText("Absolute Maximum Fitness (AMF) :");
    grid->addWidget(AbsMaxFit,0,0);
    QLabel * AbsMaxFitNum = new QLabel();
    AbsMaxFitNum->setText("0");
    AbsMaxFitNum->setObjectName("AbsMaxFitNum");
    grid->addWidget(AbsMaxFitNum,0,1);

    QLabel * firstOccurenceText = new QLabel();
    QString fo = QString("First occurence of AMF at iteration: %1").arg(0);
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
    gen->setText("Current Generation:");
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
    bestIndiv->setText("Best Individual of current generation");
    grid->addWidget(bestIndiv,6,0);

    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText("Fitness:");
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


void MainWindow::addTabAUCROC(QString name, Rain * rain, int rain_size, Activation *activation, int activation_size)
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
    QString fo = QString("First occurence of AMF at iteration: %1").arg(0);
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
    gen->setText("Current Generation:");
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
    bestIndiv->setText("Best Individual of current generation");
    grid->addWidget(bestIndiv,6,0);

    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText("Fitness:");
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


    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText(fitness);
    grid->addWidget(curMaxFit,0,0);
    QLabel * curMaxFitNum = new QLabel();
    curMaxFitNum->setText("0");
    curMaxFitNum->setObjectName("curMaxFitNum"+nameMobFunc);
    grid->addWidget(curMaxFitNum,0,1);


    QLabel * tb = new QLabel();
    tb->setText("tb:");
    grid->addWidget(tb,1,0);
    QLabel * tbNum = new QLabel();
    tbNum->setText("0");
    tbNum->setObjectName("tbNum"+nameMobFunc);
    grid->addWidget(tbNum,1,1);

    QLabel * dCritico = new QLabel();
    dCritico->setText("Safety margin:");
    grid->addWidget(dCritico,1,2);
    QLabel * dCriticoNum = new QLabel();
    dCriticoNum->setText("0");
    dCriticoNum->setObjectName("dCriticoNum"+nameMobFunc);
    grid->addWidget(dCriticoNum,1,3);

    QLabel * momPrimo = new QLabel();
    momPrimo->setText("First-order momentum:");
    grid->addWidget(momPrimo,1,4);
    QLabel * momPrimoNum = new QLabel();
    momPrimoNum->setText("0");
    momPrimoNum->setObjectName("momPrimoNum"+nameMobFunc);
    grid->addWidget(momPrimoNum,1,5);

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
    kerFunc->setSizePolicy(spUp);
    kerFunc->setObjectName("kerFunc");
    vertical->addWidget(kerFunc);

    horizontalSplitter->addWidget(wrap(vertical));


    QSplitter* verticalSplitterGMDeGMDn = new QSplitter();
    verticalSplitterGMDeGMDn->setOrientation(Qt::Horizontal);
    //GMD ------------------------------------
    QVBoxLayout * mainLGMD = new QVBoxLayout();
    getGraphs("kerFunc","GMD","Fitness GMD :", mainLGMD, rain, rain_size, activation_size, activation, mobFuncGMD);

    verticalSplitterGMDeGMDn->addWidget(wrap(mainLGMD));

    //GMDn ------------------------------------
    QVBoxLayout * mainLGMDn = new QVBoxLayout();
    getGraphs("kerFunc","GMDn","Fitness GMDn :", mainLGMDn, rain, rain_size, activation_size, activation, mobFuncGMDn);

    verticalSplitterGMDeGMDn->addWidget(wrap(mainLGMDn));

    horizontalSplitter->addWidget(verticalSplitterGMDeGMDn);

    QSplitter* verticalSplitterEW = new QSplitter();
    verticalSplitterEW->setOrientation(Qt::Horizontal);

    //EW ------------------------------------
    QVBoxLayout * mainLEW = new QVBoxLayout();
    getGraphs("kerFunc","EW","Fitness EW :", mainLEW, rain, rain_size, activation_size, activation, mobFuncEW);


    verticalSplitterEW->addWidget(wrap(mainLEW));

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

    verticalSplitterEW->addWidget(rightside);

    horizontalSplitter->addWidget(verticalSplitterEW);
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
    int i = ui->treeWidget->indexOfTopLevelItem(item);
    //cout << i << endl;
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
    QAction *delAct = new QAction(QIcon(""), tr("&Delete Project"), this);
    QAction *show = new QAction(QIcon(""), tr("&Show Result"), this);
    QTreeWidgetItem *item = ui->treeWidget->itemAt( pos );
    connect(show, SIGNAL(triggered()),this, SLOT(openFolderProject()),Qt::UniqueConnection) ;
    connect(delAct, SIGNAL(triggered()),signalMapper, SLOT(map()),Qt::UniqueConnection) ;//
    //this, deleteProject(QString));//item->data(0,Qt::UserRole).toString() });
    signalMapper -> setMapping(delAct,item->data(0,Qt::UserRole).toInt());
    connect (signalMapper, SIGNAL(mapped(int )), this, SLOT(deleteProject(int)),Qt::UniqueConnection) ;


    QMenu menu(this);
    menu.addAction(delAct);
    menu.addAction(show);

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
