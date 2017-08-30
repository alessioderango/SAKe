#ifndef MYVALIDATORDOUBLE_H
#define MYVALIDATORDOUBLE_H
#include <QDoubleValidator>
#include <stdio.h>
using namespace std;

class MyValidatorDouble : public QDoubleValidator
{
public:
    MyValidatorDouble(double bottom, double top, int decimals, QObject * parent) :
        QDoubleValidator(bottom, top, decimals, parent)
    {
    }

    QValidator::State validate(QString &s, int &i) const
    {
        if (s.isEmpty() && QString::compare(s,"0.",Qt::CaseInsensitive)) {
            return QValidator::Intermediate;
        }

        bool ok;
        double d = s.toDouble(&ok);

        if (ok && std::abs(d- bottom())<=std::abs(std::min(d, bottom())) && std::abs(d- top())<=std::abs(std::min(d, top()))) {
            //cout <<"valid " << d << " > " << bottom() << " && " << d << " < " << top() << endl;
            return QValidator::Acceptable;
        } else {
            //cout <<"invalid " << d << " > " << bottom() << " && " << d << " < " << top() << endl;
            return QValidator::Invalid;
        }
    }
};
#endif // MYVALIDATORDOUBLE_H
