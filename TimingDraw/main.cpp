#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "signal.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Signal signal;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Signal", &signal);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

