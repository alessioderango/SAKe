#ifndef XMLMANAGER_H
#define XMLMANAGER_H
#include <QtXml>
#include <TreeModel.h>
#include <QString>

class XMLManager
{
public:
    XMLManager(QObject *_listProjects);
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
                                      QString probabilityOfCrossover,
                                      QString probabilityOfMutation,
                                      QString pme,
                                      QString pmb,
                                      QString pattern,
                                      QString pathRains,
                                      QString pathActivation
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
                                                  QString probabilityOfCrossover,
                                                  QString probabilityOfMutation,
                                                  QString pme,
                                                  QString pmb,
                                                  QString pattern,
                                                  QString pathRains,
                                                  QString pathActivation
                                                  );
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
                                     const  QString &_percentageWeight,
                                     const  QString &numberProcessor,
                                     const  QString &_numberGamma,
                                     const  QString& _percentageGammaA,
                                     const  QString &_percentageGammaB,
                                     const  QString &_numberLinear,
                                     const  QString& _percentageLinearA,
                                     const  QString &_percentageLinearB,
                                     const  QString &maxGeneration,
                                     const  QString &_fileKernel,
                                     std::vector<std::vector<double> > matrixGamma1,
                                     std::vector<std::vector<double> > matrixGamma2,
                                     std::vector<std::vector<double> > matrixLinear
                                     );
    int SaveXMLFileAlreadyExistRegressionProject(const QString &_projectName,
                                                 const QString &selection,
                                                 const QString &value1,
                                                 const QString &value2,
                                                 const QString &populationSize,
                                                 const QString &percentageCrossover,
                                                 const QString &percentageMutation,
                                                 const  QString &_percentageWeight,
                                                 const  QString &numberProcessor,
                                                 const  QString &_numberGamma,
                                                 const  QString& _percentageGammaA,
                                                 const  QString &_percentageGammaB,
                                                 const  QString &_numberLinear,
                                                 const  QString& _percentageLinearA,
                                                 const  QString &_percentageLinearB,
                                                 const  QString &maxGeneration,
                                                 const  QString &_fileKernel);


    int findProjectName(QString nameProject);
    QString xmlFilePath;
    QVariantList getAllElementsFromProjectName(QString nameProject);


    TreeModel *getTreeview();
    void setTreeview(TreeModel *value);

private:
    QObject * listProjects;
    TreeModel * treeview;
};

#endif // XMLMANAGER_H
