#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "codemodel.h"
#include "slot.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CodeModel codeModel;



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("CodeModel", &codeModel);
    qmlRegisterType<Slot>("ase.sorsa.slot", 1, 0, "Slot");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}

