#ifndef UPDATEPROJECTS_H
#define UPDATEPROJECTS_H
#include "update.h"
#include <QMetaObject>
#include <QVariant>

class UpdateProjects: public QObject
{
    Q_OBJECT
public:
    UpdateProjects(QObject *_currentMaximumFitness,
                   QObject *_absoluteMaximumFitness,
                   QObject *_currentAverageFitness,
                   QObject *_absoluteAverageFitness,
                   QObject *_gen,
                   QObject *__tb,
                   QObject *__deltaCritico,
                   QObject *__momentoDelPrimoOrdine,
                   Update * _update,
                   QObject *__currentMaximumFitnessRegression,
                   QObject *__absoluteMaximumFitnessRegression,
                   QObject *__currentAverageFitnessRegression,
                   QObject *__absoluteAverageFitnessRegression,
                   QObject *__genRegression);
    UpdateProjects(Update *_update);
    void UpdateProjectsRegression(QObject *__currentMaximumFitnessRegression,
                                  QObject *__absoluteMaximumFitnessRegression,
                                  QObject *__currentAverageFitnessRegression,
                                  QObject *__absoluteAverageFitnessRegression,
                                  QObject *__genRegression);
    void UpdateProjectsSAke(QObject *__currentMaximumFitness,
                            QObject *__absoluteMaximumFitness,
                            QObject *__currentAverageFitness,
                            QObject *__absoluteAverageFitness,
                            QObject *__gen,
                            QObject *__tb,
                            QObject *__deltaCritico,
                            QObject *__momentoDelPrimoOrdine);


public slots:
    void updateCurrentMaximumFitness(QString);
    void updateAbosulteMaximumFitness(QString s);
    void updateCurrentAvarageFitness(QString s);
    void updateAbsoluteAvarageFitness(QString s);
    void updateGen(QString s);
    void updateTb(QString s);
    void updateDeltaCritico(QString s);
    void updateMomentoDelPrimoOrdine(QString s);

    void updateCurrentMaximumFitnessRegression(QString);
    void updateAbsoluteMaximumFitnessRegression(QString);
    void updateCurrentAvarageFitnessRegression(QString);
    void updateAbsoluteAvarageFitnessRegression(QString);
    void updateGenRegression(QString);

private:
    QObject *_currentMaximumFitness;
    QObject *_absoluteMaximumFitness ;
    QObject *_currentAverageFitness;
    QObject *_absoluteAverageFitness;
    QObject *_gen;
    QObject *_tb;
    QObject *_deltaCritico;
    QObject *_momentoDelPrimoOrdine;
    Update * update;

    QObject *_currentMaximumFitnessRegression;
    QObject *_absoluteMaximumFitnessRegression;
    QObject *_currentAverageFitnessRegression;
    QObject *_absoluteAverageFitnessRegression;
    QObject *_genRegression;
    QObject *_tbRegression;

};

#endif // UPDATEPROJECTS_H
