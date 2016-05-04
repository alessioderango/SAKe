#include "CustomPlotItem.h"
#include <QtWidgets/QApplication>
#include <QtQuick>
#include <QDeclarativeView>
#include "xmlmanager.h"


#include "SAKeStart.h"
#include "Qt"
#include "CustomPlotMobilityFunction.h"
#include "CustomPlotRegression.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    srand (time(NULL));

    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    qmlRegisterType<CustomPlotMobilityFunction>("CustomPlotMobilityFunction", 1, 0, "CustomPlotMobilityFunction");
    qmlRegisterType<CustomPlotKernel>("CustomPlotKernel", 1, 0, "CustomPlotKernel");
    qmlRegisterType<CustomPlotRegression>("CustomPlotRegression", 1, 0, "CustomPlotRegression");

    QQmlApplicationEngine engine;


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
    QObject *listProjects = rootObject->findChild<QObject*>("ListProjects");

    // load main xml with number of Projects and names


    XMLManager * xmlmanager = new XMLManager(listProjects);
    xmlmanager->ReadMainXML();

    SAKeStart * sakeStart = new SAKeStart(&engine,&a,xmlmanager);
    engine.rootContext()->setContextProperty("sakeStart", sakeStart);

    return a.exec();
}

