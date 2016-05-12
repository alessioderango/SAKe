#include "CustomPlotItem.h"
#include <QtWidgets/QApplication>
#include <QtQuick>
#include <QDeclarativeView>
#include "xmlmanager.h"
#include "SAKeStart.h"
#include "Qt"
#include "CustomPlotMobilityFunction.h"
#include "CustomPlotRegression.h"
#include "TreeModel.h"


static void initStandardTreeModel(QStandardItemModel *model)
{
//    QStandardItem *item;
//    item = new QStandardItem(QLatin1String("Row 1 Item"));
//    model->insertRow(0, item);

//    item = new QStandardItem(QLatin1String("Row 2 Item"));
//    item->setCheckable(true);
//    model->insertRow(1, item);

//    QStandardItem *childItem = new QStandardItem(QLatin1String("Row 2 Child Item"));
//    item->setChild(0, childItem);

//    item = new QStandardItem(QLatin1String("Row 3 Item"));
//    item->setIcon(QIcon());
//    model->insertRow(2, item);

    auto childEntry = new QStandardItem( "CAIO" );
    //childEntry->setData();
    //childEntry->setData( description, TreeModel_Role_Description );
    //childEntry->parent();
    QStandardItem* entry;
    auto entries = model->findItems( "branchName" );
    if ( entries.count() > 0 )
    {
        entry = entries.at(0);
    }
    else
    {
        entry = new QStandardItem( "branchName" );
        model->appendRow( entry );
    }
    entry->appendRow( childEntry );
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    srand (time(NULL));

    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    qmlRegisterType<CustomPlotMobilityFunction>("CustomPlotMobilityFunction", 1, 0, "CustomPlotMobilityFunction");
    qmlRegisterType<CustomPlotKernel>("CustomPlotKernel", 1, 0, "CustomPlotKernel");
    qmlRegisterType<CustomPlotRegression>("CustomPlotRegression", 1, 0, "CustomPlotRegression");
    qmlRegisterType<TreeModel>("ca.imaginativethinking.tutorials.models", 1, 0, "TreeModel" );

    QQmlApplicationEngine engine;
    TreeModel* model = new TreeModel();
    engine.rootContext()->setContextProperty("theModel", model);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
    QObject *listProjects = rootObject->findChild<QObject*>("ListProjects");
//    TreeModel *theModel = rootObject->findChild<TreeModel*>("theModel");

    // load main xml with number of Projects and names


    XMLManager * xmlmanager = new XMLManager(listProjects);
    xmlmanager->setTreeview(model);
    xmlmanager->ReadCalibrationProjectXML();
//    xmlmanager->SaveXMLFileValidationProject("CIAO","RainPath","ActivationPath","kernelPath","folderSave");
    //xmlmanager->SaveXMLFileAlreadyExistValidationProject("CIAO","RainPath1","ActivationPath1","kernelPath1","folderSave1");

    SAKeStart * sakeStart = new SAKeStart(&engine,&a,xmlmanager);
    engine.rootContext()->setContextProperty("sakeStart", sakeStart);

    return a.exec();
}

