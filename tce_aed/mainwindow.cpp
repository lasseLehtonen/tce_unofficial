#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTabBar>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    project_(nullptr),
    asmCodePage_(nullptr)
{
    ui->setupUi(this);
    ui->actionSave->setDisabled(true);
    asmCodePage_ = new AsmCodePage(this);
    QObject::connect(asmCodePage_, SIGNAL(modified()), this, SLOT(on_projectModifed()));
    ui->tabWidget->addTab(asmCodePage_, "N/A code");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_projectModifed()
{
    ui->actionSave->setEnabled(true);
    ui->actionSave_as->setEnabled(true);
}

void MainWindow::on_projectClosed()
{
    qDebug() << "Closing project";
    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);
    ui->actionInfo->toggled(false);
    ui->actionInfo->setChecked(false);
    ui->actionAssembly_code_editor->toggled(false);
    ui->actionAssembly_code_editor->setChecked(false);

    ui->tabWidget->clear();

    if (project_) {
        delete project_;
        project_ = nullptr;
    }

    if (asmCodePage_) {
        delete asmCodePage_;
    }
    asmCodePage_ = new AsmCodePage(this);
}

void MainWindow::on_action_Quit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNewProject_triggered()
{
    if (project_) {
        // There's already a project.
        QMessageBox box(this);
        box.setText("Current project has been modified.");
        box.setInformativeText("Do you want to save the project?");
        box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Cancel);
        int retval = box.exec();

        switch (retval) {
        case QMessageBox::Cancel:
            return;
        case QMessageBox::Save:
            project_->saveProject();
            break;
        case QMessageBox::Discard:
            break;
        }
        on_projectClosed();
    }

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Create new project"), "", tr("TCE Projects (*.tceprj)"));

    project_ = new Project(fileName, this);
    QObject::connect(project_, SIGNAL(modified()), this, SLOT(on_projectModifed()));

    project_->newProject();
    asmCodePage_->createNew();
    ui->actionInfo->toggled(true);
    ui->actionInfo->setChecked(true);
    ui->actionAssembly_code_editor->toggled(true);
    ui->actionAssembly_code_editor->setChecked(true);

}

void MainWindow::on_actionSave_triggered()
{
    project_->saveProject();
    asmCodePage_->saveFile(project_->projectFolderName() + project_->asmCodeFileName());
    ui->actionSave->setDisabled(true);
}

void MainWindow::on_actionSave_as_triggered()
{

}

void MainWindow::on_actionInfo_toggled(bool arg1)
{
}

void MainWindow::on_actionAssembly_code_editor_toggled(bool arg1)
{
    if (arg1) {
        if (project_) {
            ui->tabWidget->addTab(asmCodePage_, project_->asmCodeFileName());
        } else {
            ui->tabWidget->addTab(asmCodePage_, "N/A code");
        }
    } else {
        int idx = ui->tabWidget->indexOf(asmCodePage_);
        ui->tabWidget->removeTab(idx);
    }
}

void MainWindow::on_actionOpenProject_triggered()
{
    if (project_) {
        // There's already a project.
        QMessageBox box(this);
        box.setText("Current project has been modified.");
        box.setInformativeText("Do you want to save the project?");
        box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Cancel);
        int retval = box.exec();

        switch (retval) {
        case QMessageBox::Cancel:
            return;
        case QMessageBox::Save:
            project_->saveProject();
            break;
        case QMessageBox::Discard:
            break;
        }
        on_projectClosed();
    }

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open project"), "", tr("TCE Projects (*.tceprj)"));

    project_ = new Project(fileName, this);
    QObject::connect(project_, SIGNAL(modified()), this, SLOT(on_projectModifed()));

    project_->loadProject();
    asmCodePage_->loadFile(project_->projectFolderName() + project_->asmCodeFileName());
    ui->actionInfo->toggled(true);
    ui->actionInfo->setChecked(true);
    ui->actionAssembly_code_editor->toggled(true);
    ui->actionAssembly_code_editor->setChecked(true);
}

void MainWindow::on_actionBeautify_triggered()
{
    asmCodePage_->beautify();
}

void MainWindow::on_actionInsert_row_above_triggered()
{
    asmCodePage_->insertRowAbove();
}

void MainWindow::on_actionInsert_row_below_triggered()
{
    asmCodePage_->insertRowBelow();
}

void MainWindow::on_actionInsert_column_left_triggered()
{
    asmCodePage_->insertColumnLeft();
}

void MainWindow::on_actionInsert_column_right_triggered()
{
    asmCodePage_->insertColumnRight();
}

void MainWindow::on_actionDelete_column_triggered()
{
    asmCodePage_->deleteColumns();
}

void MainWindow::on_actionDelete_row_triggered()
{
    asmCodePage_->deleteRows();
}

void MainWindow::on_actionCopy_triggered()
{
    asmCodePage_->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    asmCodePage_->paste();
}

void MainWindow::on_actionCut_triggered()
{
    asmCodePage_->cut();
}

void MainWindow::on_actionClear_triggered()
{
    asmCodePage_->clear();
}

void MainWindow::on_actionUndo_triggered()
{
    asmCodePage_->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    asmCodePage_->redo();
}
