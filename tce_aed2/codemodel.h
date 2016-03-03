#ifndef CODEMODEL_H
#define CODEMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QPair>
#include <QDebug>
#include <QColor>
#include "code.h"

class CodeModel: public QObject
{
private:
    Q_OBJECT
    const int MAX_BUSES = 1023;
public:
    CodeModel();

public:

signals:
    void colorChanged();
    void columnInserted(int column);
    void rowInserted(int row);
    void columnUpdated(int column);
    void tableWidthChanged(double newWidth);


public slots:
    int rowCount() const;
    int columnCount() const;

    bool setCode(int row, int column, QString data);
    QString code(int row, int column);

    void selection(int row, int column);
    void deselection(int row, int column);
    void deselectAll();
    QColor getColor(int row, int column);
    bool isSelected(int row, int column);
    void copy();
    void cut();
    void paste();
    void save();

    void addColumnLeft();
    void addColumnRight();
    void addRowAbove();
    void addRowBelow();

    void alignColumn(int column);

    void slotWidth(int row, int column, double width);
    double columnWidth(int column);

private:
    quint32 rows_;
    quint32 columns_;
    QMap<QPair<int, int>, bool> selections_;
    QMap<QPair<int, int>, Code> code_;
    QMap<QPair<int, int>, double> slotWidth_;
    int currentRow_;
    int currentColumn_;
};

#endif // CODEMODEL_H
