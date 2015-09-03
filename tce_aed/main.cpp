#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(on_action_Quit_triggered()));

    w.show();

    return a.exec();
}
