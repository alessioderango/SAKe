#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "validation.h"

std::vector<QThread *> MainWindow::threads;

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
    signalMapper = new QSignalMapper(this);
    connect (this, SIGNAL(expandTreeViewSignals()), this, SLOT(expandTreeViewSlot())) ;


}


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
    customPlot->xAxis->setLabel( "Generation" );
    customPlot->yAxis->setLabel( "Fitness" );
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange( 0, 20 );
    customPlot->yAxis->setRange( 0, 1.05 );

    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestFitness(QPoint)));

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
    customPlot->yAxis->setLabel("y");


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

void MainWindow::makeKernelPlot(QCustomPlot *customPlot)
{
    QCPBars* myBars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(myBars);
    // now we can modify properties of myBars:
    myBars->setName("Bars Series 1");
    customPlot->xAxis->setLabel("kernel");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange( 0,180 );
    customPlot->yAxis->setRange( -0.01,0.25 );
    customPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequestKernel(QPoint)));

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

void MainWindow::updateTexts(int indexTab,
                             QString s,
                             QString fitness,
                             QString cuavfitness,
                             QString tb,
                             QString safetyMargin,
                             QString momentum,
                             int barValue, int firstOccurence)
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
    QString fo = QString("first occurence at %1 iteration").arg(firstOccurence);
    bestfndatItera->setText(fo);
    QProgressBar* bar = (QProgressBar*)tabs->findChild<QProgressBar*>("bar");
    bar->setValue(barValue);
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

void MainWindow::updateMobPlot(int indexTab, Rain * rain, int rain_size, Activation *activation, int activation_size, std::vector<double> Y, double YmMinVal, tm YmMinTime, double YmMinVal2, tm  YmMinTime2, std::vector<Ym> bests, std::vector<QCPItemText*> widgetArray,
                               std::vector<QCPItemLine*> arrowArray)
{
    QCustomPlot *m_CustomPlot = getPlotMobility(indexTab);
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

QCustomPlot* MainWindow::getPlotMobility(int indexTab){
    QTabWidget* tabs = (QTabWidget*)ui->tabWidget_2->widget(indexTab);
    QCustomPlot* tab = (QCustomPlot*)tabs->findChild<QCustomPlot*>("mobFunc");
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

void MainWindow::addTab(QString name, Rain * rain, int rain_size, Activation *activation, int activation_size)
{
    QTabWidget * tabwidget = new QTabWidget();
    tabwidget->setObjectName("tabwidget");
    QCustomPlot * customPlot = new QCustomPlot();
    //customPlot->setOpenGl(true,64);
    QCustomPlot * mobFunc = new QCustomPlot();
    QCustomPlot * kerFunc = new QCustomPlot();
    ui->tabWidget_2->addTab(tabwidget, name);
    QWidget * tab1=ui->tabWidget_2->widget(ui->tabWidget_2->count()-1);
    QVBoxLayout * mainL = new QVBoxLayout();

    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spUp.setVerticalStretch(2);
    QVBoxLayout * vertical = new QVBoxLayout();
    MainWindow::makeFitnessPlot(customPlot);
    customPlot->setSizePolicy(spUp);
    customPlot->setObjectName("fitFunc");
    vertical->addWidget(customPlot);
    MainWindow::makeKernelPlot(kerFunc);
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
    QLabel * gen = new QLabel();
    gen->setText("Current Generation:");
    grid->addWidget(gen,0,0);
    QLabel * genNum = new QLabel();
    genNum->setText("0");
    genNum->setObjectName("GenerationText");
    grid->addWidget(genNum,0,1);



    QLabel * AbsMaxFit = new QLabel();
    AbsMaxFit->setText("Absolute Maximum Fitness:");
    grid->addWidget(AbsMaxFit,1,0);
    QLabel * AbsMaxFitNum = new QLabel();
    AbsMaxFitNum->setText("0");
    AbsMaxFitNum->setObjectName("AbsMaxFitNum");
    grid->addWidget(AbsMaxFitNum,1,1);



    QLabel * AbsAveFit = new QLabel();
    AbsAveFit->setText("Absolute Average Fitness:");
    grid->addWidget(AbsAveFit,2,0);
    QLabel * AbsAveFitNum = new QLabel();
    AbsAveFitNum->setText("0");
    AbsAveFitNum->setObjectName("AbsAveFitNum");
    grid->addWidget(AbsAveFitNum,2,1);

    QLabel * bestIndiv = new QLabel();
    bestIndiv->setText("Best Individual:");
    grid->addWidget(bestIndiv,3,0);

    QLabel * curMaxFit = new QLabel();
    curMaxFit->setText("Maximum Fitness:");
    grid->addWidget(curMaxFit,4,0);
    QLabel * curMaxFitNum = new QLabel();
    curMaxFitNum->setText("0");
    curMaxFitNum->setObjectName("curMaxFitNum");
    grid->addWidget(curMaxFitNum,4,1);

    QLabel * curAveFit = new QLabel();
    curAveFit->setText("Average Fitness:");
    grid->addWidget(curAveFit,4,2);
    QLabel * curAveFitNum = new QLabel();
    curAveFitNum->setText("0");
    curAveFitNum->setObjectName("curAveFitNum");
    grid->addWidget(curAveFitNum,4,3);

    QLabel * tb = new QLabel();
    tb->setText("tb:");
    grid->addWidget(tb,5,0);
    QLabel * tbNum = new QLabel();
    tbNum->setText("0");
    tbNum->setObjectName("tbNum");
    grid->addWidget(tbNum,5,1);

    QLabel * dCritico = new QLabel();
    dCritico->setText("Safety margin:");
    grid->addWidget(dCritico,5,2);
    QLabel * dCriticoNum = new QLabel();
    dCriticoNum->setText("0");
    dCriticoNum->setObjectName("dCriticoNum");
    grid->addWidget(dCriticoNum,5,3);

    QLabel * momPrimo = new QLabel();
    momPrimo->setText("First-order momentum:");
    grid->addWidget(momPrimo,5,4);
    QLabel * momPrimoNum = new QLabel();
    momPrimoNum->setText("0");
    momPrimoNum->setObjectName("momPrimoNum");
    grid->addWidget(momPrimoNum,5,5);


    // first occurence at N iteration;

    QLabel * firstOccurenceText = new QLabel();
    QString fo = QString("first occurence at %1 iteration").arg(0);
    firstOccurenceText->setText(fo);
    firstOccurenceText->setObjectName("firstOccurenceText");
    grid->addWidget(firstOccurenceText,6,0);


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
    MainWindow::makeKernelPlot(kerFunc);
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
    cout << i << endl;
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
