#include "codemodel.h"
#include <QByteArray>

CodeModel::CodeModel() :
    rows_(3),
    columns_(3),
    currentRow_(0),
    currentColumn_(0)
{    
}

int CodeModel::rowCount() const
{
    return rows_;
}

int CodeModel::columnCount() const
{
    return columns_;
}


bool CodeModel::setCode(int row, int column, QString data)
{
    QString old = code(row, column);
    if (old == data) {
        return false;
    }


    qDebug() << "setCode()" << data << "to" << QPair<int, int>(row, column-1);
    Code c;
    c.code(data);
    code_[QPair<int, int>(row, column-1)] = c;
    qDebug() << "Ass" << code_[QPair<int, int>(row, column-1)].asString();
    alignColumn(column);
    return true;
}

QString CodeModel::code(int row, int column)
{
    QPair<int, int> loc(row, column-1);
    if (code_.find(loc) != code_.end()) {
        return code_[loc].asString();
    } else {
        return "...";
    }
}


QColor CodeModel::getColor(int row, int column)
{
    if (selections_.find(QPair<int, int>(row, column)) != selections_.end() && selections_[QPair<int, int>(row, column)] == true) {
        if (row == currentRow_ && column == currentColumn_) {
            return QColor("#ce93d8");
        }
        if (row % 2 == 0) {
            return QColor("#f8bbd0");
        } else {
            return QColor("#f48fb1");
        }
    } else {
        return QColor("transparent");
    }
}

bool CodeModel::isSelected(int row, int column)
{
    if (selections_.find(QPair<int, int>(row, column)) != selections_.end() && selections_[QPair<int, int>(row, column)] == true) {
        return true;
    } else {
        return false;
    }
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
    qDebug() << "Save()" << rows_ << "x" << columns_;
}

void CodeModel::addColumnLeft()
{
    deselectAll();
    selection(currentRow_, currentColumn_);
    columns_++;
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        if(iter.key().second < currentColumn_) {
            temp[QPair<int, int>(iter.key().first, iter.key().second)] = iter.value();
        } else {
            temp[QPair<int, int>(iter.key().first, iter.key().second + 1)] = iter.value();
        }
    }
    code_ = temp;
    qDebug() << "emit columnInserted" << currentColumn_;
    emit columnInserted(currentColumn_);
}

void CodeModel::addColumnRight()
{
    deselectAll();
    selection(currentRow_, currentColumn_);
    columns_++;
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        if(iter.key().second < currentColumn_+1) {
            temp[QPair<int, int>(iter.key().first, iter.key().second)] = iter.value();
        } else {
            temp[QPair<int, int>(iter.key().first, iter.key().second + 1)] = iter.value();
        }
    }
    code_ = temp;
    qDebug() << "emit columnInserted" << currentColumn_+1;
    emit columnInserted(currentColumn_+1);
}

void CodeModel::addRowAbove()
{
    deselectAll();
    selection(currentRow_, currentColumn_);
    rows_++;
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        if(iter.key().first < currentRow_) {
            temp[QPair<int, int>(iter.key().first, iter.key().second)] = iter.value();
        } else {
            temp[QPair<int, int>(iter.key().first + 1, iter.key().second)] = iter.value();
        }
    }
    code_ = temp;
    emit rowInserted(currentRow_);
}

void CodeModel::addRowBelow()
{
    deselectAll();
    selection(currentRow_, currentColumn_);
    rows_++;
    QMap<QPair<int, int>, Code> temp;
    for (auto iter = code_.begin(); iter != code_.end(); ++iter) {
        if(iter.key().first < currentRow_+1) {
            temp[QPair<int, int>(iter.key().first, iter.key().second)] = iter.value();
        } else {
            temp[QPair<int, int>(iter.key().first + 1, iter.key().second)] = iter.value();
        }
    }
    code_ = temp;
    emit rowInserted(currentRow_+1);
}

void CodeModel::alignColumn(int column)
{
    qDebug() << "AlignColumn" << column;
    int maxPadding = 0;
    QVector<int> paddings;
    for(int r = 0; r < rows_; ++r) {
        int c = 0;
        if (code_.find(QPair<int, int>(r, column-1)) != code_.end()) {
            c = code_[QPair<int, int>(r, column-1)].padding();
        }
        paddings.push_back(c);
        maxPadding =  c > maxPadding ? c : maxPadding;
    }

    QVector<int> r;
    r.push_back(Qt::UserRole + column);

    for(int row = 0; row < rows_; ++row) {
        if (code_.find(QPair<int, int>(row, column)) != code_.end()) {
            code_[QPair<int, int>(row, column)].setPadding(maxPadding - paddings.at(row));
        }
    }
}

void CodeModel::slotWidth(int row, int column, double width)
{
    QPair<int, int> idx(row, column);
    if(slotWidth_.find(idx) != slotWidth_.end()) {
        if (slotWidth_[idx] == width) {
            return;
        }
    }


    slotWidth_[idx] = width;
    emit columnUpdated(column);

    double sum = 0.0;
    for (int i = 0; i < columnCount(); ++i) {
        sum += columnWidth(i);
    }
    emit tableWidthChanged(sum);
}

double CodeModel::columnWidth(int column)
{
    double retval = 100.0;
    for (int row = 0; row < rows_; ++row) {
        QPair<int, int> idx(row, column);
        if (slotWidth_.find(idx) != slotWidth_.end()) {
            double tmp = slotWidth_[idx];
            retval = tmp > retval ? tmp : retval;
        }
    }
    return retval;
}

void CodeModel::selection(int row, int column)
{
    currentRow_ = row;
    currentColumn_ = column;
    selections_[QPair<int, int>(row, column)] = true;
    emit colorChanged();
    qDebug() << "Selecting" << row << column;
}

void CodeModel::deselection(int row, int column)
{
    selections_[QPair<int, int>(row, column)] = false;
    emit colorChanged();
    qDebug() << "Deselecting" << row << column;
}

void CodeModel::deselectAll()
{
    selections_.clear();
    emit colorChanged();
    qDebug() << "Deselecting all";
}


