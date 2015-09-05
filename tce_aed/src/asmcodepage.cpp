#include "asmcodepage.h"
#include <QDebug>

AsmCodePage::AsmCodePage(QWidget *parent) : QTableView(parent)
{
    delegate_ = new AsmCodeCellDelegate(this);
    model_ = new AsmCodeModel(2, 2, this);


    QModelIndex index = model_->index(0, 0);
    QVariant v = QString("data");
    model_->setData(index, v);

    setModel(model_);
    setItemDelegate(delegate_);
}

AsmCodePage::~AsmCodePage()
{

}

void AsmCodePage::createNew()
{
    initialize();


    /*
    setRowCount(5);
    setColumnCount(2);
    setItem(0, 0, new QTableWidgetItem("CODE;"));
    setItem(2, 0, new QTableWidgetItem(":procedure main;"));
    setItem(3, 0, new QTableWidgetItem("main:"));
    */

}

bool AsmCodePage::loadFile(QString fileName)
{
    return true;
}

bool AsmCodePage::saveFile(QString fileName)
{
    return true;
}

void AsmCodePage::on_cellChanged(int row, int col)
{
    qDebug() << "Cell changed at" << row << col;
}

void AsmCodePage::initialize()
{
    //QWidget::connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(on_cellChanged(int, int)));
}

