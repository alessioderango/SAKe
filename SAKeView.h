#ifndef SAKEVIEW_H
#define SAKEVIEW_H

#include <QObject>
#include "SAke/SAKeController.h"
class SAKeView : public QObject
{
    Q_OBJECT
public:
     SAKeView();


public slots:
    void InitAlgo();

signals:

};

#endif // SAKEVIEW_H
