#ifndef MYEVENTFILTER
#define MYEVENTFILTER
#include <QObject>
#include "SAke/SAKeController.h"

class MyEventFilter : public QObject
 {
     Q_OBJECT
  public:
    void setSake(SAKeController* _sake){
        sake=_sake;
    }

 protected:
     bool eventFilter(QObject *obj, QEvent *event) {
//          qDebug() << "close " << "\n";
         if (event->type() == QEvent::Close)
         {
             //sake->stopThread();
             return true;
         } else
         {
             // standard event processing
             return QObject::eventFilter(obj, event);
         }
     }
 private:
     SAKeController* sake;
 };



#endif // MYEVENTFILTER

