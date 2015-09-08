#ifndef ASMCODEMODEL_H
#define ASMCODEMODEL_H

#include <QObject>
#include <QVariant>
#include <QAbstractTableModel>
#include <vector>

#include "common.h"
#include "asmcodeslot.h"

class AsmCodeModel : public QAbstractTableModel
{
    Q_OBJECT
public:

public:
    AsmCodeModel(QObject* parent);
    AsmCodeModel(int rows, int columns, QObject* parent);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    void beautify(void);

    CodeType type(const QModelIndex& index) const;
    QString source(const QModelIndex& index) const;
    QString destination(const QModelIndex& index) const;

    int columnLength(int column) const;
    std::vector<int> sourceLengths(void) const;


signals:
    void cellChanged(int row, int column);

public slots:
    void dataChange(const QModelIndex &index);

private slots:

private:

    std::vector<int> cellSourceWidths_;
    std::vector<std::vector<AsmCodeSlot>> slots_;



};

#endif // ASMCODEMODEL_H
