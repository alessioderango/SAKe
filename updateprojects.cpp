#include "updateprojects.h"

UpdateProjects::UpdateProjects( Update * _update)
{
    update=_update;
}

void UpdateProjects::UpdateProjectsSAke(QObject *__currentMaximumFitness,
                                        QObject *__absoluteMaximumFitness,
                                        QObject *__currentAverageFitness,
                                        QObject *__absoluteAverageFitness,
                                        QObject *__gen,
                                        QObject *__tb,
                                        QObject *__deltaCritico,
                                        QObject *__momentoDelPrimoOrdine,
                                        QObject *_progressBar)
{
    _currentMaximumFitness = __currentMaximumFitness;
    _absoluteMaximumFitness = __absoluteMaximumFitness;
    _currentAverageFitness = __currentAverageFitness;
    _absoluteAverageFitness = __absoluteAverageFitness;
    _gen =__gen;
    _tb=__tb;
    _deltaCritico=__deltaCritico;
    _momentoDelPrimoOrdine=__momentoDelPrimoOrdine;
    progressBar = _progressBar;

    QObject::connect(update, SIGNAL(valueCurrentMaximumFitness(QString)),this, SLOT( updateCurrentMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteMaximumFitness(QString)),this, SLOT( updateAbosulteMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueCurrentAvarageFitness(QString)),this, SLOT( updateCurrentAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteAvarageFitness(QString)),this, SLOT( updateAbsoluteAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueGen(QString)),this, SLOT( updateGen(QString)));
    QObject::connect(update, SIGNAL(valueTb(QString)),this, SLOT( updateTb(QString)));
    QObject::connect(update, SIGNAL(valueDeltaCritico(QString)),this, SLOT( updateDeltaCritico(QString)));
    QObject::connect(update, SIGNAL(valueMomentoDelPrimoOrdine(QString)),this, SLOT( updateMomentoDelPrimoOrdine(QString)));
    QObject::connect(update, SIGNAL(valueProgressBar(QString)),this, SLOT( updateProgressBar(QString)));

}

void UpdateProjects::UpdateProjectsRegression(QObject *__currentMaximumFitnessRegression,
                                              QObject *__absoluteMaximumFitnessRegression,
                                              QObject *__currentAverageFitnessRegression,
                                              QObject *__absoluteAverageFitnessRegression,
                                              QObject *__genRegression,
                                              QObject *_progressBar)
{
    _currentMaximumFitnessRegression = __currentMaximumFitnessRegression;
    _absoluteMaximumFitnessRegression = __absoluteMaximumFitnessRegression;
    _currentAverageFitnessRegression= __currentAverageFitnessRegression;
    _absoluteAverageFitnessRegression = __absoluteAverageFitnessRegression;
    _genRegression = __genRegression;
    progressBar = _progressBar;

    QObject::connect(update, SIGNAL(valueCurrentMaximumFitnessRegression(QString)),this, SLOT( updateCurrentMaximumFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteMaximumFitnessRegression(QString)),this, SLOT( updateAbsoluteMaximumFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueCurrentAvarageFitnessRegression(QString)),this, SLOT( updateCurrentAvarageFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteAvarageFitnessRegression(QString)),this, SLOT( updateAbsoluteAvarageFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueGenRegression(QString)),this, SLOT( updateGenRegression(QString)));
    QObject::connect(update, SIGNAL(valueProgressBar(QString)),this, SLOT( updateProgressBar(QString)));

}

UpdateProjects::UpdateProjects(QObject *__currentMaximumFitness,
                               QObject *__absoluteMaximumFitness,
                               QObject *__currentAverageFitness,
                               QObject *__absoluteAverageFitness,
                               QObject *__gen,
                               QObject *__tb,
                               QObject *__deltaCritico,
                               QObject *__momentoDelPrimoOrdine,
                               Update * _update,
                               QObject *__currentMaximumFitnessRegression,
                               QObject *__absoluteMaximumFitnessRegression,
                               QObject *__currentAverageFitnessRegression,
                               QObject *__absoluteAverageFitnessRegression,
                               QObject *__genRegression
                               , QObject *_progressBar)
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
    progressBar = _progressBar;
    QObject::connect(update, SIGNAL(valueCurrentMaximumFitness(QString)),this, SLOT( updateCurrentMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteMaximumFitness(QString)),this, SLOT( updateAbosulteMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueCurrentAvarageFitness(QString)),this, SLOT( updateCurrentAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteAvarageFitness(QString)),this, SLOT( updateAbsoluteAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueGen(QString)),this, SLOT( updateGen(QString)));
    QObject::connect(update, SIGNAL(valueTb(QString)),this, SLOT( updateTb(QString)));
    QObject::connect(update, SIGNAL(valueDeltaCritico(QString)),this, SLOT( updateDeltaCritico(QString)));
    QObject::connect(update, SIGNAL(valueMomentoDelPrimoOrdine(QString)),this, SLOT( updateMomentoDelPrimoOrdine(QString)));

    QObject::connect(update, SIGNAL(valueProgressBar(QString)),this, SLOT( updateProgressBar(QString)));

    _currentMaximumFitnessRegression = __currentMaximumFitnessRegression;
    _absoluteMaximumFitnessRegression = __absoluteMaximumFitnessRegression;
    _currentAverageFitnessRegression= __currentAverageFitnessRegression;
    _absoluteAverageFitnessRegression = __absoluteAverageFitnessRegression;
    _genRegression = __genRegression;

    QObject::connect(update, SIGNAL(valueCurrentMaximumFitnessRegression(QString)),this, SLOT( updateCurrentMaximumFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteMaximumFitnessRegression(QString)),this, SLOT( updateAbsoluteMaximumFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueCurrentAvarageFitnessRegression(QString)),this, SLOT( updateCurrentAvarageFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteAvarageFitnessRegression(QString)),this, SLOT( updateAbsoluteAvarageFitnessRegression(QString)));
    QObject::connect(update, SIGNAL(valueGenRegression(QString)),this, SLOT( updateGenRegression(QString)));

}

void UpdateProjects::updateProgressBar(QString s){
    progressBar->setProperty("value",s);
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


void UpdateProjects::updateCurrentMaximumFitnessRegression(QString s)
{
    _currentMaximumFitnessRegression->setProperty("text",s);
}

void UpdateProjects::updateAbsoluteMaximumFitnessRegression(QString s)
{
    _absoluteMaximumFitnessRegression->setProperty("text",s);
}

void UpdateProjects::updateCurrentAvarageFitnessRegression(QString s )
{
    _currentAverageFitnessRegression->setProperty("text",s);
}

void UpdateProjects::updateAbsoluteAvarageFitnessRegression(QString s)
{
    _absoluteAverageFitnessRegression->setProperty("text",s);
}

void UpdateProjects::updateGenRegression(QString s)
{
    _genRegression->setProperty("text",s);
}
