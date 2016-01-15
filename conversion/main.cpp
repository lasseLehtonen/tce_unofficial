#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "worker.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Worker worker;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Engine", &worker);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

