#include "updateprojects.h"

UpdateProjects::UpdateProjects(QObject *__currentMaximumFitness,
                               QObject *__absoluteMaximumFitness,
                               QObject *__currentAverageFitness,
                               QObject *__absoluteAverageFitness,
                               QObject *__gen,
                               Update * _update)
{

    _currentMaximumFitness = __currentMaximumFitness;
    _absoluteMaximumFitness = __absoluteMaximumFitness;
    _currentAverageFitness = __currentAverageFitness;
    _absoluteAverageFitness = __absoluteAverageFitness;
    _gen =__gen;

    update=_update;
    QObject::connect(update, SIGNAL(valueCurrentMaximumFitness(QString)),this, SLOT( updateCurrentMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteMaximumFitness(QString)),this, SLOT( updateAbosulteMaximumFitness(QString)));
    QObject::connect(update, SIGNAL(valueCurrentAvarageFitness(QString)),this, SLOT( updateCurrentAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueAbsoluteAvarageFitness(QString)),this, SLOT( updateAbsoluteAvarageFitness(QString)));
    QObject::connect(update, SIGNAL(valueGen(QString)),this, SLOT( updateGen(QString)));

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
