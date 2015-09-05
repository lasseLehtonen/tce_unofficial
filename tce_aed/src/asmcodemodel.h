#ifndef ASMCODEMODEL_H
#define ASMCODEMODEL_H

#include <QObject>
#include <QVariant>
#include <QAbstractTableModel>
#include <vector>

#include "asmcodeslot.h"

class AsmCodeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    AsmCodeModel(QObject* parent);
    AsmCodeModel(int rows, int columns, QObject* parent);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    const AsmCodeSlot& codeSlot(const QModelIndex & index) const;

signals:

public slots:

private:
    int rows_;
    int columns_;

    std::vector<std::vector<AsmCodeSlot>> slots_;



};

#endif // ASMCODEMODEL_H
