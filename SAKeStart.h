#ifndef SAKESTART_H
#define SAKESTART_H

#include <QObject>
#include <QQmlComponent>
#include "CustomPlotItem.h"
#include "CustomPlotRegression.h"
#include "SAke/SAKeController.h"
#include "Regression/regressioncontroller.h"
#include "MyEventFilter.h"
#include <QMetaObject>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <qapplication.h>
#include "xmlmanager.h"
#include "update.h"
#include "validationcontroller.h"
#include "controlpoints.h"


class SAKeStart : public QObject
{
    Q_OBJECT
public:
    explicit SAKeStart(QQmlApplicationEngine* engine,QApplication * a,XMLManager * xmlManager,QObject *parent = 0);

    string getSelection() const;
    void setSelection(const string &value);

    string getReplecament() const;
    void setReplecament(const string &value);

    int getPopSize() const;
    void setPopSize(int value);

    int getMaxGen() const;
    void setMaxGen(int value);

    float getRelRateCrossover() const;
    void setRelRateCrossover(float value);

    float getRelRateMutation() const;
    void setRelRateMutation(float value);

    float getPropMutation() const;
    void setPropMutation(float value);

    float getPropCrossover() const;
    void setPropCrossover(float value);

    float getTbMin() const;
    void setTbMin(float value);

    float getTbMax() const;
    void setTbMax(float value);

    float getDHpMin() const;
    void setDHpMin(float value);

    float getDHpMax() const;
    void setDHpMax(float value);

    float getPme() const;
    void setPme(float value);

    float getPmb() const;
    void setPmb(float value);

    string getPattern() const;
    void setPattern(const string &value);
    void update();

signals:

public slots:
    void openFile(const QVariant &filePath);
    void stopSAKeController(int count);
    void stopValidationController(int count);
    void stopRegressionController(int count);
    void InitAlgo(const QVariant &selection,
                  const QVariant &pop,
                  const QVariant &maxGen,
                  const QVariant &tbMax,
                  const QVariant &tbMin,
                  const QVariant &dHpMax,
                  const QVariant &dHpMin,
                  const QVariant &propSelection,
                  const QVariant &propCrossover,
                  const QVariant &propMutation,
                  const QVariant &pme,
                  const QVariant &pmb,
                  const QVariant &pattern,
                  const QVariant &filename,
                  const QVariant &filenameActivaion,
                  const QVariant &_projectName,
                  const QVariant &_numberProcessor,
                  const QVariant &_para1,
                  const QVariant &_para2,
                  const QVariant &thresholdKernel,
                  const QVariant &tipo,
                  const QVariant &typeAlgorithm,
                  const QVariant &selectionOrder1,
                  const QVariant &selectionOrder2,
                  const QVariant &selectionOrder3,
                  const QVariant &selectionOrder4,
                  const QVariant &numberElitist,
                  const QVariant &seed,
                  const QVariant &saveKernels);
    void startValidation(
            const QVariant &_projectName,
            const QVariant &filenameRainPath,
            const QVariant &filenameActivaionPath,
            const QVariant &filenameKernelPath,
            const QVariant &filenameKenrelPath
            );
    void startRegression(const QVariant &_projectaname,
                         const QVariant &selection,
                         const QVariant &selectionElitist,
                         const QVariant &populationSize,
                         const QVariant &percentageCrossover,
                         const QVariant &percentageMutation,
                         const  QVariant &numberProcessor,
                         const  QVariant &maxGeneration,
                         const  QVariant &fileurl,
                         const QVariant &tipo,
                         const QVariantList &matrxGamma1,
                         const QVariantList &matrxGamma2,
                         const QVariantList &matrixLinear,
                         const QVariant &checkControlpoints,
                         const QVariant &checkKernel,
                         const QVariant &checkN,
                         const QVariant &checkControlPointsWithN,
                         const QVariant &textN,
                         const QVariant &para1,
                         const QVariant &para2,
                         const QVariant &typeReplacement,
                         const QVariant &typeProject);




    int existProjectName(const QVariant &_projectName);
    QVariantList getAllElementsFromProjectName(const QVariant &_projectName);
    bool deleteProject(const QVariant &  idProject);
    //    void updateCurrentMaximumFitness(QString);
    //    void updateAbosulteMaximumFitness(QString s);
    //    void updateCurrentAvarageFitness(QString s);
    //    void updateAbsoluteAvarageFitness(QString s);
    //    void updateGen(QString s);

private:
    string selection;
    string replecament;
    int popSize;
    int maxGen;
    int numberProject;
    int numberProjectRegression;
    float relRateCrossover;
    float relRateMutation;
    float propMutation;
    float propCrossover;
    float tbMin;
    float tbMax;
    float dHpMin;
    float dHpMax;
    float Pme;
    float Pmb;
    string projectName;
    int numberProcessor;
    string pattern;
    double thresholdKernel;
    QQmlApplicationEngine* engine;
    QApplication * a;
    //    QObject *_currentMaximumFitness;
    //    QObject *_absoluteMaximumFitness ;
    //    QObject *_currentAverageFitness;
    //    QObject *_absoluteAverageFitness;
    //    QObject *_gen;
    XMLManager * xmlManager;

    std::vector<QThread*> threadsController;




};

#endif // SAKESTART_H
