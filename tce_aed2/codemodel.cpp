#include "codemodel.h"
#include <QByteArray>
#include <cmath>

CodeModel::CodeModel() :
    currentRow_(0),
    currentColumn_(0)
{    
    setRows(3);
    setColumns(3);
}

int CodeModel::rows() const
{
    return m_rows;
}

int CodeModel::columns() const
{
    return m_columns;
}

double CodeModel::codeWidth() const
{
    return m_codeWidth;
}

double CodeModel::slotWidth(int row, int column) const
{
    QPair<int, int> slot(row, column);
    if (slotWidth_.find(slot) != slotWidth_.end()) {
        return slotWidth_[slot];
    }
    return 100.0;
}

double CodeModel::columnWidth(int column) const
{
    if (columnWidth_.find(column) != columnWidth_.end()) {
        return columnWidth_[column];
    }
    return 100.0;
}

QString CodeModel::setCode(int row, int column, QString data)
{
    QString old = code(row, column);
    if (old == data) {
        return data;
    }

    Code c;
    c.code(data);
    code_[QPair<int, int>(row, column)] = c;
    //qDebug() << "Ass" << code_[QPair<int, int>(row, column)].asString() << code_[QPair<int, int>(row, column)].type();
    alignColumn(column);
    return code_[QPair<int, int>(row, column)].asString();
}

QString CodeModel::code(int row, int column)
{
    QPair<int, int> loc(row, column);
    if (code_.find(loc) != code_.end()) {
        return code_[loc].asString();
    }
    return "";
}



void CodeModel::copy()
{

}

void CodeModel::cut()
{

}

void CodeModel::paste()
{

}

void CodeModel::save()
{
    qDebug() << "Save()" << rows() << "x" << columns();
}

void CodeModel::updateCodeWidth()
{
    double width = 0.0;
    for (int col = 0; col < columns(); ++col) {
        width += columnWidth(col);
    }
    setCodeWidth(width);
}

void CodeModel::updateCodeHeight()
{
    setCodeHeight(rows() * 24);
}

double CodeModel::codeHeight() const
{
    return m_codeHeight;
}

void CodeModel::addColumnLeft()
{
    qDebug() << "add to left of" << currentColumn_;
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        int R = iter.key().first;
        int C = iter.key().second;
        if(iter.key().second < currentColumn_) {
            qDebug() << R << C << "->" << R << C;
            temp[QPair<int, int>(R, C)] = iter.value();
        } else {
            qDebug() << R << C << "->" << R << C+1;
            temp[QPair<int, int>(R, C + 1)] = iter.value();
        }
    }
    code_ = temp;
    setColumns(columns()+1);
    updateCodeWidth();
}

void CodeModel::addColumnRight()
{
    qDebug() << "add to right of" << currentColumn_;
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        if(iter.key().second < currentColumn_+1) {
            temp[QPair<int, int>(iter.key().first, iter.key().second)] = iter.value();
        } else {
            temp[QPair<int, int>(iter.key().first, iter.key().second + 1)] = iter.value();
        }
    }

    code_ = temp;
    setColumns(columns()+1);
    updateCodeWidth();
}

void CodeModel::addRowAbove()
{
    setRows(rows()+1);
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        if(iter.key().first < currentRow_) {
            temp[QPair<int, int>(iter.key().first, iter.key().second)] = iter.value();
        } else {
            temp[QPair<int, int>(iter.key().first + 1, iter.key().second)] = iter.value();
        }
    }
    code_ = temp;
    updateCodeHeight();
}

void CodeModel::addRowBelow()
{
    setRows(rows()+1);
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        if(iter.key().first < currentRow_+1) {
            temp[QPair<int, int>(iter.key().first, iter.key().second)] = iter.value();
        } else {
            temp[QPair<int, int>(iter.key().first + 1, iter.key().second)] = iter.value();
        }
    }
    code_ = temp;
    updateCodeHeight();
}

void CodeModel::alignColumn(int column)
{
    qDebug() << "AlignColumn" << column;
    int maxPadding = 0;
    QVector<int> paddings;
    for(int r = 0; r < rows(); ++r) {
        int c = 0;
        if (code_.find(QPair<int, int>(r, column)) != code_.end()) {
            c = code_[QPair<int, int>(r, column)].padding();
        }
        paddings.push_back(c);
        maxPadding =  c > maxPadding ? c : maxPadding;
    }

    for(int row = 0; row < rows(); ++row) {
        if (code_.find(QPair<int, int>(row, column)) != code_.end()) {
            code_[QPair<int, int>(row, column)].setPadding(maxPadding - paddings.at(row));
        }
    }
}

void CodeModel::setRows(int rows)
{
    if (m_rows == rows)
        return;

    m_rows = rows;
    emit rowsChanged(rows);
}

void CodeModel::setColumns(int columns)
{
    if (m_columns == columns)
        return;

    m_columns = columns;
    emit columnsChanged(columns);
}

void CodeModel::setCodeWidth(double codeWidth)
{
    if (m_codeWidth == codeWidth)
        return;

    m_codeWidth = codeWidth;
    qDebug() << "codeWidth updated to" << codeWidth;
    emit codeWidthChanged(codeWidth);
}

void CodeModel::setSlotWidth(int row, int column, double width)
{
    if (std::isnan(width)) {
        return;
    }
    qDebug() << "Slot" << row << "," << column << "=" << width;

    double widest = 0.0;
    int widestRow = 0;
    for(int Row = 0; Row <= rows(); ++Row) {
        if (slotWidth(Row, column) > widest) {
            widest = slotWidth(Row, column);
            widestRow = Row;
        }
    }

    slotWidth_[QPair<int, int>(row, column)] = width;

    if (width > widest || widestRow == row) {
        columnWidth_[column] = width;
        qDebug() << "emit columnWidthChanged("<< column << ")";
        emit columnWidthChanged(column);
        updateCodeWidth();
    }

}

void CodeModel::setCodeHeight(double codeHeight)
{
    if (m_codeHeight == codeHeight)
        return;

    m_codeHeight = codeHeight;
    emit codeHeightChanged(codeHeight);
}

void CodeModel::generate()
{
    qDebug() << "Generate";
}

void CodeModel::select(int row, int column)
{
    currentRow_ = row;
    currentColumn_ = column;
    qDebug() << "Selecting" << row << column;
}


