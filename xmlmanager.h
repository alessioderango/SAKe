#ifndef XMLMANAGER_H
#define XMLMANAGER_H
#include <QtXml>

class XMLManager
{
public:
    XMLManager();
    void ReadMainXML(QVariantList &a);
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
    int findProjectName(QString nameProject);
    QString xmlFilePath;
};

#endif // XMLMANAGER_H
