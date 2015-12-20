#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QAbstractTableModel>
#include <QDebug>

#include "memoryblock.h"

class MemoryModel : public QAbstractTableModel
{
    Q_PROPERTY(QString saveFile READ saveFile NOTIFY saveFileChanged)
    Q_OBJECT

    enum MemoryModelRoles {
        NameRole = Qt::UserRole + 1,
        WidthRole,
        DepthRole,
        TypeRole
    };

public:
    explicit MemoryModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;



signals:
    void saveFileChanged();

public slots:
    void open(QString file);
    void save();
    void saveAs(QString file);
    QString saveFile();
    void addBlock(QString component, QString instance);

    void setOption(QString opt, QVariant value);

private:
    QString file_;
    QVector<MemoryBlock> blocks_;
};

#endif // MEMORYMODEL_H
