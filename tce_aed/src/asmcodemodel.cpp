#include "asmcodemodel.h"
#include "asmcodeslot.h"
#include <QDebug>

AsmCodeModel::AsmCodeModel(QObject *parent) : QAbstractTableModel(parent)
{

}

AsmCodeModel::AsmCodeModel(int rows, int columns, QObject *parent) : QAbstractTableModel(parent)
{
    std::vector<AsmCodeSlot> temp;
    temp.resize(columns, AsmCodeSlot());
    slots_.resize(rows, temp);
    cellSourceWidths_ = sourceLengths();
}

int AsmCodeModel::rowCount(const QModelIndex &parent) const
{
    return slots_.size();
}

int AsmCodeModel::columnCount(const QModelIndex &parent) const
{
    if (slots_.size() > 0) {
        return slots_.at(0).size();
    } else {
        return 0;
    }
}


QVariant AsmCodeModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

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
    slots_.at(row).at(col).setData(value.toString());
    return true;
}

Qt::ItemFlags AsmCodeModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool AsmCodeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    std::vector<AsmCodeSlot> codeRow;
    codeRow.assign(columnCount(), AsmCodeSlot());
    while(count--) {
        slots_.insert(slots_.begin()+row, codeRow);
    }
    endInsertRows();
}

bool AsmCodeModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column+count-1);
    AsmCodeSlot slot;
    for (int row = 0; row < rowCount(); ++row) {
        for(int i = 0; i < count; ++i) {
            slots_.at(row).insert(slots_.at(row).begin()+column, slot);
        }
    }
    for(int i = 0; i < count; ++i) {
        cellSourceWidths_.insert(cellSourceWidths_.begin()+column, 0);
    }
    endInsertColumns();
}

bool AsmCodeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    for (int i = 0; i < count; ++i) {
        slots_.erase(slots_.begin()+row);
    }
    endRemoveRows();
}

bool AsmCodeModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column+count-1);
    for(int row = 0; row < rowCount(); ++row) {
        slots_.at(row).erase(slots_.at(row).begin()+column, slots_.at(row).begin()+column+count);
    }
    endRemoveColumns();
}

void AsmCodeModel::beautify()
{
    cellSourceWidths_ = sourceLengths();
}

CodeType AsmCodeModel::type(const QModelIndex &index) const
{
    return slots_.at(index.row()).at(index.column()).type();
}

QString AsmCodeModel::source(const QModelIndex &index) const
{
    return slots_.at(index.row()).at(index.column()).source().leftJustified(cellSourceWidths_.at(index.column()));
}

QString AsmCodeModel::destination(const QModelIndex &index) const
{
    return slots_.at(index.row()).at(index.column()).destination();
}

int AsmCodeModel::columnLength(int column) const
{
    std::vector<int> sourceWidths = sourceLengths();
    int retval = 0;
    for (int row = 0; row < rowCount(); ++row) {
        int length = sourceWidths.at(column) + 4
                + slots_.at(row).at(column).destination().size();
        if (length > retval) {
            retval = length;
        }
    }
    return retval;
}

std::vector<int> AsmCodeModel::sourceLengths() const
{
    std::vector<int> sourceLens;
    sourceLens.assign(columnCount(), 0);
    for (int row = 0; row < rowCount(); ++row) {
        for (int col = 0; col < columnCount(); ++col) {
            if (slots_.at(row).at(col).source().size() > sourceLens.at(col)) {
                sourceLens.at(col) = slots_.at(row).at(col).source().size();
            }
        }
    }
    return sourceLens;
}

void AsmCodeModel::dataChange(const QModelIndex &index)
{
    dataChanged(index, index);
    cellChanged(index.row(), index.column());
}


