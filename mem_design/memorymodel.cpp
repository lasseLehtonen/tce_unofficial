#include "memorymodel.h"
#include <QFile>
#include <QFileInfo>

MemoryModel::MemoryModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void MemoryModel::open(QString file)
{

    QFile fin(file);
    qDebug() << "Open file: " << fin.fileName();
    fin.open(QIODevice::ReadOnly);
    if (!fin.isOpen()) {
        qDebug() << "Couldn't open file: " << file;
    }
    file_ = file;

}

void MemoryModel::save()
{
    qDebug() << "Save file: " << file_;
    QFile fout(file_);
}

void MemoryModel::saveAs(QString file)
{
    QFile fout(file);
    qDebug() << "Save as file: " << fout.fileName();
    file_ = fout.fileName();
    emit saveFileChanged();

}

QString MemoryModel::saveFile()
{
    QFileInfo info(file_);
    return info.fileName();
}


int MemoryModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "RowCount";
    return blocks_.size() + 1;
}

int MemoryModel::columnCount(const QModelIndex &parent) const
{
    qDebug() << "ColumnCount";
    return 1;
}

QVariant MemoryModel::data(const QModelIndex &index, int role) const
{
    if (role == NameRole)
        return "kissa";
    if (role == WidthRole)
        return 32;
    if (role == DepthRole)
        return 1024;
    if (role == TypeRole)
        return "Single-port";

}

QHash<int, QByteArray> MemoryModel::roleNames() const
{
    QHash<int, QByteArray> map;
    map[NameRole] = "name";
    map[DepthRole] = "depth";
    map[WidthRole] = "width";
    map[TypeRole] = "type";
    return map;
}

void MemoryModel::addBlock(QString component, QString instance)
{
    beginInsertRows(QModelIndex(), blocks_.size(), blocks_.size());
    MemoryBlock block(component, instance);
    blocks_.push_back(block);
    endInsertRows();
}

void MemoryModel::setOption(QString opt, QVariant value)
{
    qDebug() << "set" << opt << "to" << value;
}
