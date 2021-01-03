#ifndef QTPRINTDOCUMENT_WRAP_H
#define QTPRINTDOCUMENT_WRAP_H

#include "document.h"
#include <QObject>

class Wrap : public QObject {
Q_OBJECT
public slots:

    void start();
    void startDialog();
    void endDialog();
    void fillDialog(Qpd::Document *doc);
    void startDialog2();
    void print(QPainter *, Qpd::Document *);

signals:

    void finished();
};


#endif //QTPRINTDOCUMENT_WRAP_H
