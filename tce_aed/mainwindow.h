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

    void on_actionBeautify_triggered();

    void on_actionInsert_row_above_triggered();

    void on_actionInsert_row_below_triggered();

    void on_actionInsert_column_left_triggered();

    void on_actionInsert_column_right_triggered();

    void on_actionDelete_column_triggered();

    void on_actionDelete_row_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionClear_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::MainWindow *ui;
    Project* project_;
    AsmCodePage* asmCodePage_;
};

#endif // MAINWINDOW_H
