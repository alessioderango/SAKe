#ifndef XMLMANAGER_H
#define XMLMANAGER_H
#include <QtXml>

class XMLManager
{
public:
    XMLManager(QObject *_listProjects);
    void ReadMainXML();
    int SaveXMLFile(QString name,
                     QString selection,
                     QString value1,
                     QString value2,
                     QString numberProcessor,
                     QString populationSize,
                     QString maximumNumberOfGenerations,
                     QString tbMax,
                     QString tbMin,
                     QString dHpMax,
                     QString dHpMin,
                     QString probabilityOfCrossover,
                     QString probabilityOfMutation,
                     QString pme,
                     QString pmb,
                     QString pattern,
                     QString pathRains,
                     QString pathActivation
                     );
    int SaveXMLFileAlreadyExist(QString name,
                     QString selection,
                     QString value1,
                     QString value2,
                     QString numberProcessor,
                     QString populationSize,
                     QString maximumNumberOfGenerations,
                     QString tbMax,
                     QString tbMin,
                     QString dHpMax,
                     QString dHpMin,
                     QString probabilityOfCrossover,
                     QString probabilityOfMutation,
                     QString pme,
                     QString pmb,
                     QString pattern,
                     QString pathRains,
                     QString pathActivation
                     );
    int findProjectName(QString nameProject);
    QString xmlFilePath;
    QVariantList getAllElementsFromProjectName(QString nameProject);

private:
    QObject * listProjects;
};

#endif // XMLMANAGER_H
