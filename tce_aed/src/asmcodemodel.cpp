#include "asmcodemodel.h"
#include <QDebug>

AsmCodeModel::AsmCodeModel(QObject *parent) : QAbstractTableModel(parent),
    rows_(0),
    columns_(0)
{

}

AsmCodeModel::AsmCodeModel(int rows, int columns, QObject *parent) : QAbstractTableModel(parent),
    rows_(rows),
    columns_(columns)
{
    std::vector<AsmCodeSlot> temp;
    temp.resize(columns, AsmCodeSlot());
    slots_.resize(rows, temp);
}

int AsmCodeModel::rowCount(const QModelIndex &parent) const
{
    return rows_;
}

int AsmCodeModel::columnCount(const QModelIndex &parent) const
{
    return columns_;
}

QVariant AsmCodeModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col  = index.column();

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        return slots_.at(row).at(col).data();
    default:
        return "";
    }
}

bool AsmCodeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col  = index.column();
    qDebug() << row << col << value.toString();
    slots_.at(row).at(col).setData(value.toString());
    return true;
}

Qt::ItemFlags AsmCodeModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

const AsmCodeSlot &AsmCodeModel::codeSlot(const QModelIndex &index) const
{
    int row = index.row();
    int col  = index.column();
    return slots_.at(row).at(col);
}


