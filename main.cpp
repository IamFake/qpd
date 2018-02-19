#include <QProcess>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QTimer>

#include "wrap.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);

    Wrap w;
    QObject::connect(&w, &Wrap::finished, &app, &QGuiApplication::quit);

    QTimer::singleShot(0, &w, &Wrap::start);

    return app.exec();
}