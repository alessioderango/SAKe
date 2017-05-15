#ifndef UPDATE
#define UPDATE
#include <QObject>

class Update : public QObject
{
    Q_OBJECT
public:

signals:
    void valueCurrentMaximumFitness(QString);
    void valueAbsoluteMaximumFitness(QString);
    void valueCurrentAvarageFitness(QString);
    void valueAbsoluteAvarageFitness(QString);
    void valueGen(QString);
    void valueTb(QString);
    void valueDeltaCritico(QString);
    void valueMomentoDelPrimoOrdine(QString);
    void valueProgressBar(QString);

    void valueCurrentMaximumFitnessRegression(QString);
    void valueAbsoluteMaximumFitnessRegression(QString);
    void valueCurrentAvarageFitnessRegression(QString);
    void valueAbsoluteAvarageFitnessRegression(QString);
    void valueGenRegression(QString);

};

#endif // UPDATE

