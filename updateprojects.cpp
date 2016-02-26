#include "updateprojects.h"

UpdateProjects::UpdateProjects(QObject *__currentMaximumFitness,
                               QObject *__absoluteMaximumFitness,
                               QObject *__currentAverageFitness,
                               QObject *__absoluteAverageFitness,
                               QObject *__gen,
                               QObject *__tb,
                               QObject *__deltaCritico,
                               QObject *__momentoDelPrimoOrdine,
                               Update * _update)
{

    _currentMaximumFitness = __currentMaximumFitness;
    _absoluteMaximumFitness = __absoluteMaximumFitness;
    _currentAverageFitness = __currentAverageFitness;
    _absoluteAverageFitness = __absoluteAverageFitness;
    _gen =__gen;
    _tb=__tb;
    _deltaCritico=__deltaCritico;
    _momentoDelPrimoOrdine=__momentoDelPrimoOrdine;

    update=_update;
    QObject::connect(update, SIGNAL(valueCurrentMaximumFitness(QString)),this, SLOT( updateCurrentMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteMaximumFitness(QString)),this, SLOT( updateAbosulteMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueCurrentAvarageFitness(QString)),this, SLOT( updateCurrentAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteAvarageFitness(QString)),this, SLOT( updateAbsoluteAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueGen(QString)),this, SLOT( updateGen(QString)));
    QObject::connect(update, SIGNAL(valueTb(QString)),this, SLOT( updateTb(QString)));
    QObject::connect(update, SIGNAL(valueDeltaCritico(QString)),this, SLOT( updateDeltaCritico(QString)));
    QObject::connect(update, SIGNAL(valueMomentoDelPrimoOrdine(QString)),this, SLOT( updateMomentoDelPrimoOrdine(QString)));
}

void UpdateProjects::updateCurrentMaximumFitness(QString s){

    _currentMaximumFitness->setProperty("text",s);
}

void UpdateProjects::updateAbosulteMaximumFitness(QString s){

    _absoluteMaximumFitness->setProperty("text",s);
}

void UpdateProjects::updateCurrentAvarageFitness(QString s){

    _currentAverageFitness->setProperty("text",s);
}

void UpdateProjects::updateAbsoluteAvarageFitness(QString s){

    _absoluteAverageFitness->setProperty("text",s);
}
void UpdateProjects::updateGen(QString s){

    _gen->setProperty("text",s);
}
void UpdateProjects::updateTb(QString s){

    _tb->setProperty("text",s);
}
void UpdateProjects::updateDeltaCritico(QString s){

    _deltaCritico->setProperty("text",s);
}
void UpdateProjects::updateMomentoDelPrimoOrdine(QString s){

    _momentoDelPrimoOrdine->setProperty("text",s);
}
