#include "CustomPlotItem.h"
#include <QtWidgets/QApplication>
#include <QtQuick>
#include <QQuickView>
#include "xmlmanager.h"
#include "SAKeStart.h"
#include "Qt"
#include "CustomPlotMobilityFunction.h"
#include "CustomPlotRegression.h"
#include "CustomPlotRegressionPreviewKernel.h"
#include "TreeModel.h"
#include "TableModel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QApplication a(argc, argv);

    //srand (time(NULL));

    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    qmlRegisterType<CustomPlotMobilityFunction>("CustomPlotMobilityFunction", 1, 0, "CustomPlotMobilityFunction");
    qmlRegisterType<CustomPlotKernel>("CustomPlotKernel", 1, 0, "CustomPlotKernel");
    qmlRegisterType<CustomPlotRegression>("CustomPlotRegression", 1, 0, "CustomPlotRegression");
    qmlRegisterType<CustomPlotRegressionPreviewKernel>("CustomPlotRegressionPreviewKernel", 1, 0, "CustomPlotRegressionPreviewKernel");
//    qmlRegisterType<TableModel>("TableModel", 1, 0, "TableModel" );

    QQmlApplicationEngine engine;
    TreeModel* model = new TreeModel();
    TableModel * modelTable = new TableModel();
    engine.rootContext()->setContextProperty("theModel", model);
    engine.rootContext()->setContextProperty("TableModel", modelTable);


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

