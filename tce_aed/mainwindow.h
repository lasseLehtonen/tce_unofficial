#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "src/project.h"
#include "src/asmcodepage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_projectModifed();

    void on_projectClosed();

    void on_action_Quit_triggered();

    void on_actionNewProject_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionInfo_toggled(bool arg1);

    void on_actionAssembly_code_editor_toggled(bool arg1);

    void on_actionOpenProject_triggered();

private:
    Ui::MainWindow *ui;
    Project* project_;
    AsmCodePage* asmCodePage_;
};

#endif // MAINWINDOW_H
