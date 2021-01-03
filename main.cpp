#include <QApplication>
#include <QTimer>

#include "wrap.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Wrap w;
    QObject::connect(&w, &Wrap::finished, &app, &QGuiApplication::quit);

//    QTimer::singleShot(0, &w, &Wrap::start); // print to pdf
    QTimer::singleShot(0, &w, &Wrap::startDialog2); // preview dialog

    return app.exec();
}