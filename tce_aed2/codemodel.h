#ifndef CODEMODEL_H
#define CODEMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QPair>
#include <QDebug>
#include <QColor>
#include <QQmlListProperty>
#include "code.h"

class CodeModel: public QObject
{
private:
    Q_OBJECT
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(double codeWidth READ codeWidth WRITE setCodeWidth NOTIFY codeWidthChanged)
    Q_PROPERTY(double codeHeight READ codeHeight WRITE setCodeHeight NOTIFY codeHeightChanged)

    const int MAX_BUSES = 1023;
public:
    CodeModel();

public:

    int rows() const;
    int columns() const;
    double codeWidth() const;
    Q_INVOKABLE double slotWidth(int row, int column) const;
    Q_INVOKABLE double columnWidth(int column) const;

    void updateCodeWidth();
    void updateCodeHeight();

    double codeHeight() const;

signals:


    void rowsChanged(int rows);
    void columnsChanged(int columns);
    void codeWidthChanged(double codeWidth);
    void columnWidthChanged(int column);
    void codeHeightChanged(double codeHeight);


public slots:

    QString setCode(int row, int column, QString data);
    QString code(int row, int column);

    void select(int row, int column);
    void copy();
    void cut();
    void paste();
    void save();

    void addColumnLeft();
    void addColumnRight();
    void addRowAbove();
    void addRowBelow();

    void alignColumn(int column);

    void setRows(int rows);
    void setColumns(int columns);
    void setCodeWidth(double codeWidth);
    void setSlotWidth(int row, int column, double width);
    void setCodeHeight(double codeHeight);

    void generate();

private:
    QMap<QPair<int, int>, Code> code_;
    QMap<QPair<int, int>, double> slotWidth_;
    QMap<int, double> columnWidth_;
    int currentRow_;
    int currentColumn_;
    int m_rows;
    int m_columns;
    double m_codeWidth;
    double m_codeHeight;
};

#endif // CODEMODEL_H
