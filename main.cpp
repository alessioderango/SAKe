#include "CustomPlotItem.h"
#include <QtWidgets/QApplication>
#include <QtQuick>
#include <QDeclarativeView>
#include "xmlmanager.h"

#include <utils/eoParallel.h>
#include "SAKeStart.h"
#include "Qt"
#include "CustomPlotMobilityFunction.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");
    qmlRegisterType<CustomPlotMobilityFunction>("CustomPlotMobilityFunction", 1, 0, "CustomPlotMobilityFunction");
    qmlRegisterType<CustomPlotKernel>("CustomPlotKernel", 1, 0, "CustomPlotKernel");

    QQmlApplicationEngine engine;


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
 QObject *listProjects = rootObject->findChild<QObject*>("ListProjects");

 // load main xml with number of Projects and names
 QVariant returnedValue;
 QVariantList projects;

 XMLManager * xmlmanager = new XMLManager();
 xmlmanager->ReadMainXML(projects);


 QMetaObject::invokeMethod(listProjects, "addElementList", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, QVariant::fromValue(projects)));



//   engine.load(QUrl(QStringLiteral("qrc:/parameters.qml")));
// QObject *rootObject = engine.rootObjects().first();
 
// QQmlApplicationEngine newProject;
// newProject.load(QUrl(QStringLiteral("qrc:/main.qml")));
//  QObject *newProjectObecjt = engine.rootObjects().first();
//   QObject *m_button = newProjectObecjt->findChild<QObject*>("namestart");
   


//    QObject *listProjects = rootObject->findChild<QObject*>("listProjects");


     SAKeStart * sakeStart = new SAKeStart(&engine,&a,xmlmanager);
     engine.rootContext()->setContextProperty("sakeStart", sakeStart);

//  QObject::connect(m_button, SIGNAL(qmlSignal(QVariant,QVariant,QVariant,QVariant,QVariant,QVariant,
//                                              QVariant,QVariant,QVariant,QVariant,QVariant,QVariant,
//                                              QVariant,QVariant,QVariant)),sakeStart, SLOT( InitAlgo(QVariant,QVariant,QVariant,QVariant,QVariant,QVariant,
//                                                                                                     QVariant,QVariant,QVariant,QVariant,QVariant,QVariant,
//                                                                                                     QVariant,QVariant,QVariant)));
  return a.exec();
}

