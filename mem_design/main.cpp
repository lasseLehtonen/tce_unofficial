#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "memorymodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MemoryModel memoryModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("MemoryModel", &memoryModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

