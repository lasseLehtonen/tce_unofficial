#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "codemodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CodeModel codeModel;


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("CodeModel", &codeModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

