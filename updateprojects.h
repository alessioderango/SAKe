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
    Update * _update);


public slots:
    void updateCurrentMaximumFitness(QString);
    void updateAbosulteMaximumFitness(QString s);
    void updateCurrentAvarageFitness(QString s);
    void updateAbsoluteAvarageFitness(QString s);
    void updateGen(QString s);
    void updateTb(QString s);
    void updateDeltaCritico(QString s);
    void updateMomentoDelPrimoOrdine(QString s);

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

};

#endif // UPDATEPROJECTS_H
