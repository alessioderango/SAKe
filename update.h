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

public slots:

private:


};

#endif // UPDATE

