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

    delete project_;
    project_ = nullptr;
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
    if (!asmCodePage_) {
        asmCodePage_ = new AsmCodePage(this);
    }
    asmCodePage_->createNew();
    ui->actionInfo->toggled(true);
    ui->actionInfo->setChecked(true);
    ui->actionAssembly_code_editor->toggled(true);
    ui->actionAssembly_code_editor->setChecked(true);

}

void MainWindow::on_actionSave_triggered()
{
    project_->saveProject();
    ui->actionSave->setDisabled(true);
}

void MainWindow::on_actionSave_as_triggered()
{

}

void MainWindow::on_actionInfo_toggled(bool arg1)
{
    /*
    if (arg1 && project_) {
        infoTabIndex_ = ui->tabWidget->addTab(new QTextBrowser(this), "Info");
    } else {
        ui->tabWidget->indexOf(&asmCodePage_);
        ui->tabWidget->removeTab(infoTabIndex_);
        infoTabIndex_ = -1;
    }
    */
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

    if (!asmCodePage_) {
        asmCodePage_ = new AsmCodePage(this);
    }
    project_->loadProject();
    ui->actionInfo->toggled(true);
    ui->actionInfo->setChecked(true);
    ui->actionAssembly_code_editor->toggled(true);
    ui->actionAssembly_code_editor->setChecked(true);
}
