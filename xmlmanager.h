#ifndef XMLMANAGER_H
#define XMLMANAGER_H
#include <QtXml>
#include <TreeModel.h>
#include <QString>

class XMLManager
{
public:
    XMLManager();
    void ReadCalibrationProjectXML();
    int SaveXMLFileCalibrationProject(QString name,
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
                                      QString probabilityOfSelection,
                                      QString probabilityOfCrossover,
                                      QString probabilityOfMutation,
                                      QString pme,
                                      QString pmb,
                                      QString pattern,
                                      QString pathRains,
                                      QString pathActivation,
                                      QString typeReplacement,
                                      QString numberElitist,
                                      QString seed,
                                      QString saveKernels
                                      );
    int SaveXMLFileAlreadyExistCalibrationProject(QString name,
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
                                                  QString probabilityOfSelection,
                                                  QString probabilityOfCrossover,
                                                  QString probabilityOfMutation,
                                                  QString pme,
                                                  QString pmb,
                                                  QString pattern,
                                                  QString pathRains,
                                                  QString pathActivation,
                                                  QString typeReplacement,
                                                  QString numberElitist
                                                  , QString seed, QString saveKernels);
    int SaveXMLFileValidationProject(const QString &_projectName,
                                     const QString &filenameRainPath,
                                     const QString &filenameActivaionPath,
                                     const QString &filenameKernelPath,
                                     const QString &folderSave);
    int SaveXMLFileAlreadyExistValidationProject(const QString &_projectName,
                                                 const QString &filenameRainPath,
                                                 const QString &filenameActivaionPath,
                                                 const QString &filenameKernelPath,
                                                 const QString &folderSave);

    int SaveXMLFileRegressionProject(const QString &_projectName,
                                     const QString &selection,
                                     const QString &value1,
                                     const QString &value2,
                                     const QString &populationSize,
                                     const QString &percentageCrossover,
                                     const QString &percentageMutation,
                                     const  QString &numberProcessor,
                                     const  QString &maxGeneration,
                                     const  QString &_fileKernel,
                                     std::vector<std::vector<double> > matrixGamma1,
                                     std::vector<std::vector<double> > matrixGamma2,
                                     std::vector<std::vector<double> > matrixLinear,
                                     const QVariant &checkControlPointsWithN,
                                     const QVariant &textN,
                                     const QString typeExecution,
                                     QString typeReplacement,
                                     QString numberElitist);

    int SaveXMLFileAlreadyExistRegressionProject(const QString &_projectName,
                                                 const QString &selection,
                                                 const QString &value1,
                                                 const QString &value2,
                                                 const QString &populationSize,
                                                 const QString &percentageCrossover,
                                                 const QString &percentageMutation,
                                                 const  QString &numberProcessor,
                                                 const  QString &maxGeneration,
                                                 const  QString &_fileKernel,
                                                 std::vector<std::vector<double> > matrixGamma1,
                                                 std::vector<std::vector<double> > matrixGamma2,
                                                 std::vector<std::vector<double> > matrixLinear,
                                                 const QVariant &checkControlPointsWithN,
                                                 const QVariant &textN,
                                                 const QString &typeExecution,
                                                 QString typeReplacement,
                                                 QString numberElitist);


    int findProjectName(QString nameProject);
    QString xmlFilePath;
    QString folderPath;
    QVariantList getAllElementsFromProjectName(QString nameProject);
    bool deleteProject(int idProject);


    TreeModel *getTreeview();
    void setTreeview(TreeModel *value);

private:
    TreeModel * treeview;
    QDomElement getGamma1ElementXML(std::vector<std::vector<double> > matrixGamma1, QDomDocument document);
    QDomElement getGamma2ElementXML(std::vector<std::vector<double> > matrixGamma2, QDomDocument document);
    QDomElement getLinearElementXML(std::vector<std::vector<double> > matrixLinear, QDomDocument document);
};

#endif // XMLMANAGER_H
